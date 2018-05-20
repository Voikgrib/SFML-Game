
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <cmath>


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
int Kill_counter = 0;
int Boss_kills = 0;
int Difficulty = 0;
sf::RenderWindow *Pwindow;
sf::Clock *Pclock;

// Including class libs

#include"libs/animation_lib.h"
#include"libs/manager_lib.h"
#include"libs/hero_lib.h"
#include"libs/meny_lib.h"
#include"prog_part/redactor.h"
#include"libs/enemy_lib.h"
#include"libs/bullet_lib.h"
#include"libs/boss_lib.h"

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

   //==========================================//
  // Press "f" to pay respect for this kostil //
 //==========================================//
//                                          //__________________________________________\
//#define ADDER_DECLARE( cur_class )													\
void cur_class##_adder(class manager* all_objs, class cur_class* cur_massive, int max)	\
{																						\
	int i = 0;																			\
																						\
	while(i != max)																		\
	{																					\
		all_objs->add( & cur_massive[i]);												\
																						\
		i++;																			\
	}																					\
}																						\
________________________________________________________________________________________\


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int intro_start(void);
int game_start(void);
sf::Texture texture_upload(char *str);

int main_menu_proc(int cur_menu_part);
int main_menu_start(void);
void kills_setter(void);

//===================================================================
//! This programm contain my trying in graphics
//!		
//!		Author: Vladimir Gribanov
//===================================================================
int main()
{
	int my_error = 0;

	my_error = game_start();    
	//my_error = main_menu_start();

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

	int Err_code = intro_start();

	if(Err_code == 1)
		return 0;

	sf::Clock main_clock;
	sf::Time cur_time = main_clock.getElapsedTime();
	sf::Vector2f hero_position;
	sf::Time last_shoot_time;

	Pclock = &main_clock;

	int my_error = main_menu_start();////////////

	while(my_error != 1)
	{
		if(my_error == -1)
			return 0;

		my_error = main_menu_start();
	}

	sf::Texture vilka_texture;
	sf::Texture enemy_texture;
	sf::Texture hero_bullet_texture;
	sf::Texture backgrownd_texture;
	sf::Texture dead_screen_texture;
	sf::Texture heal_texture;
	sf::Texture pizza_texture[3];
	c_animation pizza_animation(3);
	pizza_animation.frame_massive[0].frame_delay = sf::seconds(2);
	pizza_animation.frame_massive[1].frame_delay = sf::seconds(0.15f);
	pizza_animation.frame_massive[2].frame_delay = sf::seconds(0.15f);

	sf::Music main_music;

	if(!main_music.openFromFile("music/main_theme.ogg"))
		assert(false);
	main_music.setLoop(true); 
	main_music.setVolume(100); 
	main_music.play();
	

	class hero main_hero;

	c_boss burger(30, 30);
	
	try
	{
		pizza_animation.frame_massive[0].texture = texture_upload("test_pizza.png");
		pizza_animation.frame_massive[1].texture = texture_upload("test_pizza_1.png");
		pizza_animation.frame_massive[2].texture = texture_upload("test_pizza_2.png");
		heal_texture = texture_upload("hp_one.png");
		dead_screen_texture = texture_upload("dead_screen.png");
		backgrownd_texture = texture_upload("backgrownd.jpg");
		hero_bullet_texture = texture_upload("shoot.png");
		enemy_texture = texture_upload("enemy.png");
		vilka_texture = texture_upload("vilka.png");
	}
	catch(char *str)
	{
		printf("!!! Error with open %s !!!\n", str);
		assert(false);
	}

	sf::Sprite backgrownd_sprite;
	sf::Sprite dead_screen_sprite;
	dead_screen_sprite.setTexture(dead_screen_texture);
	dead_screen_sprite.setOrigin(256/2, 144/2); 
	dead_screen_sprite.setPosition(screen_lengh/2, screen_high/2);
	backgrownd_sprite.setTexture(backgrownd_texture);
	backgrownd_sprite.setScale(backgr_lengh, backgr_high);
	backgrownd_sprite.setPosition(0, 0);


	int max_heal = 20;
	int max_bullets = 250;
	int current_bullet = 0;
	int max_enemy = 20;
	int cur_enemy = 0;
	int hp_position = 20;
	
	class bullet *hero_bullets = new bullet[max_bullets];
	class bullet *cur_bullet = NULL;
	class enemy *test_enemy = new enemy[max_enemy];
	class enemy_vilka vilka(100, 100, 3, 1600, 1167);			 // !
	class heals *heals_massive = new heals[max_heal];

	class manager all_objs;

	// INIT HEAL  

	int cur_heal = 0;

	while(cur_heal != max_heal)
	{
		heals_massive[cur_heal].sprite.setTexture(heal_texture);
		
		cur_heal++;
	}

	///* TEST ENTITY !
	
	vilka.sprite.setTexture(vilka_texture);
	vilka.is_alive = true;
	vilka.sprite.setTextureRect(sf::IntRect(0,0,1600,1000));
	vilka.sprite.setScale(0.5, 0.5);
	vilka.sprite.setOrigin(vilka.size.x - 50, vilka.size.y - 100);
	vilka.sprite.setPosition(0, 0);

	while(cur_enemy != max_enemy)
	{
		test_enemy[cur_enemy].sprite.setTexture(enemy_texture);
		test_enemy[cur_enemy].sprite.setOrigin(test_enemy[cur_enemy].size.x/2, test_enemy[cur_enemy].size.y/2);
		test_enemy[cur_enemy].is_alive = false;

		cur_enemy++;
	}

	// TEST ENTITY ! */
	
	all_objs.adder(hero_bullets, max_bullets, sizeof(class bullet));
	all_objs.adder(test_enemy, max_enemy, sizeof(class enemy));
	all_objs.adder(&vilka, 1, sizeof(class enemy));
	all_objs.adder(&burger, 1, sizeof(class c_boss));
	all_objs.adder(burger.m_bull_1, burger.max_1, sizeof(class bullet));
	all_objs.adder(burger.m_bull_2, burger.max_2, sizeof(class bullet));

	burger.is_alive = false;

	int num_texture = 0;

    while (window.isOpen())		// Main sycle
    {
		cur_time = main_clock.getElapsedTime();

		pizza_animation.a_run(main_clock.getElapsedTime());
		main_hero.sprite.setTexture(pizza_animation.get_cur_texture());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if(Kill_counter >= 50 && burger.is_alive == false)
		{
			burger.is_alive = true;		//boss spawn
			burger.hp = burger.max_hp;
		}
		else if(Kill_counter >= 50 && burger.is_alive == true)
			Kill_counter = 0;

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
		if(burger.is_alive == true)
		{
			burger.is_damage_get(hero_bullets, max_bullets);
			burger.super_intellect(&main_hero);
			burger.shooting(&main_hero);
			is_hero_shooted(&main_hero, burger.m_bull_1, burger.max_1);
			is_hero_shooted(&main_hero, burger.m_bull_2, burger.max_2);
			if(burger.hp < 0)
			{
				burger.is_alive = false;
				Boss_kills++;
			}
		}
		main_hero.is_alive = is_hero_alive(&main_hero);
		player_hit(&main_hero, test_enemy, max_enemy, main_clock.getElapsedTime());
		kill_dead_enemys(test_enemy, max_enemy, heals_massive, max_heal);
		enemys_set_speed(test_enemy, max_enemy, main_hero.sprite.getPosition());
		is_heal_use(&main_hero, heals_massive, max_heal);

		vilka.set_speed(main_hero.sprite.getPosition());
		vilka.respawn(main_hero.sprite.getPosition());

		if(vilka.collide(main_hero.sprite.getPosition()))
			main_hero.hp = 0;
		
		enemy_rotation(test_enemy, max_enemy);

        window.clear();
		window.draw(backgrownd_sprite);
		hp_draw(main_hero);
		heals_draw(heals_massive, max_heal);
		all_objs.run();
		if(burger.is_alive == true)
			burger.hud_draw();
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
//! This function play intro
//!
//================================================================
int intro_start(void)
{
	c_animation intro_animation(12);
	sf::Texture words;
	sf::Sprite s_word;

	intro_animation.frame_massive[0].frame_delay = sf::seconds(0.8f);
	intro_animation.frame_massive[1].frame_delay = sf::seconds(0.8f);
	intro_animation.frame_massive[2].frame_delay = sf::seconds(0.8f);
	intro_animation.frame_massive[3].frame_delay = sf::seconds(0.8f);

	intro_animation.frame_massive[4].frame_delay = sf::seconds(0.8f);
	intro_animation.frame_massive[5].frame_delay = sf::seconds(0.8f);
	intro_animation.frame_massive[6].frame_delay = sf::seconds(0.8f);
	intro_animation.frame_massive[7].frame_delay = sf::seconds(0.8f);

	intro_animation.frame_massive[8].frame_delay = sf::seconds(1);
	intro_animation.frame_massive[9].frame_delay = sf::seconds(1);
	intro_animation.frame_massive[10].frame_delay = sf::seconds(1);
	intro_animation.frame_massive[11].frame_delay = sf::seconds(4.7f);


	try
	{
		words = texture_upload("intro/word.png");

		intro_animation.frame_massive[0].texture = texture_upload("intro/intro1.png");
		intro_animation.frame_massive[1].texture = texture_upload("intro/intro2.png");
		intro_animation.frame_massive[2].texture = texture_upload("intro/intro3.png");
		intro_animation.frame_massive[3].texture = texture_upload("intro/intro4.png");

		intro_animation.frame_massive[4].texture = texture_upload("intro/intro5.png");
		intro_animation.frame_massive[5].texture = texture_upload("intro/intro6.png");
		intro_animation.frame_massive[6].texture = texture_upload("intro/intro7.png");
		intro_animation.frame_massive[7].texture = texture_upload("intro/intro8.png");

		intro_animation.frame_massive[8].texture = texture_upload("intro/intro9.png");
		intro_animation.frame_massive[9].texture = texture_upload("intro/intro10.png");
		intro_animation.frame_massive[10].texture = texture_upload("intro/intro11.png");
		intro_animation.frame_massive[11].texture = texture_upload("intro/intro12.png");
	}
	catch(char *str)
	{
		printf("!!! Error with open %s !!!\n", str);
		assert(false);
	}

	sf::Sprite intro_sprite;
	sf::Clock main_clock;
	sf::Time cur_time = main_clock.getElapsedTime();
	s_word.setTexture(words);
	s_word.setPosition(10,10);
	s_word.setScale(3, 3);
	intro_sprite.setPosition(300, 300);
	intro_sprite.setScale(3, 3);
	sf::Event event;

	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
        sf::Event event;
        while (Pwindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                Pwindow->close();
				//printf("> It is not error, it is costil! C-:\n");
				return 1;
			}
        }

		cur_time = main_clock.getElapsedTime();
		intro_animation.a_run(main_clock.getElapsedTime());
		intro_sprite.setTexture(intro_animation.get_cur_texture());

		Pwindow->clear();
		Pwindow->draw(intro_sprite);
		Pwindow->draw(s_word);
		Pwindow->display();
	}

	Pwindow->clear();	

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


//================================================================
//!
//! This function realise main menu interaction
//!
//================================================================
int main_menu_proc(int cur_menu_part)
{
	//FILE *log = fopen("menu_log","w");
	
	int my_error = 100;

	if(cur_menu_part == 0)
		my_error = 1;   
	else if(cur_menu_part == 1)
	{
		kills_setter();
		my_error = 20;
	}
		
	return my_error;
}


//=================================================================
//!
//! This function init & run main menu
//!
//=================================================================
int main_menu_start(void)
{
	c_animation pointer_animation(4);
	sf::Texture part_texture;
	sf::Sprite *part_sprites = new sf::Sprite [3];

	pointer_animation.frame_massive[0].frame_delay = sf::seconds(0.8f);
	pointer_animation.frame_massive[1].frame_delay = sf::seconds(0.2f);
	pointer_animation.frame_massive[2].frame_delay = sf::seconds(0.1f);
	pointer_animation.frame_massive[3].frame_delay = sf::seconds(0.1f);

	try
	{
		pointer_animation.frame_massive[0].texture = texture_upload("main_menu/cursor_1.png");
		pointer_animation.frame_massive[1].texture = texture_upload("main_menu/cursor_2.png");
		pointer_animation.frame_massive[2].texture = texture_upload("main_menu/cursor_3.png");
		pointer_animation.frame_massive[3].texture = texture_upload("main_menu/cursor_4.png");

		part_texture = texture_upload("main_menu/menu_textures.png");
	}
	catch(char *str)
	{
		printf("!!! Error with open %s !!!\n", str);
		assert(false);
	}

	part_sprites[0].setTexture(part_texture);
	part_sprites[0].setOrigin(0, 0);
	part_sprites[0].setPosition(300, 200);
	part_sprites[0].setTextureRect(sf::IntRect(0, 0, 256, 37));

	part_sprites[1].setTexture(part_texture);
	part_sprites[1].setOrigin(0, 0);
	part_sprites[1].setPosition(300, 250);
	part_sprites[1].setTextureRect(sf::IntRect(0, 38, 256, 37));

	part_sprites[2].setTexture(part_texture);
	part_sprites[2].setOrigin(0, 0);
	part_sprites[2].setPosition(300, 300);
	part_sprites[2].setTextureRect(sf::IntRect(0, 76, 256, 37));

	c_menu main_menu(part_sprites, 3,  &pointer_animation, &pointer_animation);

	int ret = main_menu.menu_call(main_menu_proc);

	delete [] part_sprites;

	return ret;
}


//========================================================================================
//! 
//! This function contain redactor (NI) and reader from pipe of start kills 
//!
//========================================================================================
void kills_setter(void)
{
	int ret = redactor_main_body();

	if(ret < 0)
	{
		printf(">>> Error in compiller");
		assert(false);
	}
	else if(ret > 0)
	{
		printf(">>> It's okay, but i need to stop the game c:");
		assert(false);
	}	

	//	FILE *pipe = fopen("prog_part/pipe.txt","r");
	FILE *pipe = fopen("pipe.txt","r");
	int c = fgetc(pipe);

	if('0' <= c && c <= '9')
		Kill_counter = (c - 48) * 10;
	else
	{
		printf("ERROR IN PIPE FILE\n");
		assert(1 == 0);
	}

	printf("KK = %d\n", Kill_counter);
}















