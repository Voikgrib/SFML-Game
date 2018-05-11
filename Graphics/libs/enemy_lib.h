
//=======================================================================
//!
//! This library realise enemy class and so on
//!
//=======================================================================


//
// Vilka enemy
//
class enemy_vilka : public game_obj
{
	public:

	//class my_vector<int> speed;
	//class my_vector<int> size;

	//bool is_alive;

	int hp;
	int max_hp;
	int max_speed;

	//sf::Sprite sprite;

	enemy_vilka(int nhp, int nm_hp, int nmax_speed, int size_x, int size_y)
	{
		hp = nhp;
		max_hp = nm_hp;
		max_speed = nmax_speed;
		size.x = size_x;
		size.y = size_y;

		is_alive = false;
	}


	// FUNCTIONS

	virtual void move(void) override
	{
		printf("enemy_move\n");

		if(is_alive == true)  // + is_player on tarelka?
		{
			printf("enemy_move 1\n");
			sprite.move(speed.x, speed.y);
			printf("enemy_move 2\n");
		}
	}

	virtual void draw(void) override
	{
		if(is_alive == true)
			Pwindow->draw(sprite);
	}

	// Non wirtual functions

	void respawn(sf::Vector2f hero_position)
	{
		sf::Vector2f cur_enemy_position = sprite.getPosition();

		if(speed.x == 0 && speed.y == 0 && cur_enemy_position.x < 750 && hero_position.x > 750)		// Right part of screen
		{
			sprite.setScale(-0.5, 0.5);
			sprite.setPosition(1500, 0);
		}
		else if(speed.x == 0 && speed.y == 0 && cur_enemy_position.x > 750 && hero_position.x < 750) // Left part of screen
		{
			sprite.setScale(0.5, 0.5);
			sprite.setPosition(0, 0);
		}
	}

	//
	// This function set vilka speed
	//
	void set_speed(sf::Vector2f hero_position)
	{
		sf::Vector2f cur_enemy_position = sprite.getPosition();
	
		if(is_alive == true && is_pizza_not_on_plane(hero_position))
		{
			if((int)cur_enemy_position.x > (int)hero_position.x + max_speed * 2)
			{
				speed.x = -max_speed; 
				//speed.y = 0;
			}
			if((int)cur_enemy_position.x < (int)hero_position.x - max_speed * 2)
			{
				speed.x = max_speed; 
				//speed.y = 0;
			}
			if((int)cur_enemy_position.y > (int)hero_position.y + max_speed * 2)
			{
				speed.y = -max_speed; 
				//speed.x = 0;
			}
			if((int)cur_enemy_position.y < (int)hero_position.y - max_speed * 2)
			{
				speed.y = max_speed; 
				//speed.x = 0;
			}
		}
		else if(cur_enemy_position.x > 750 && cur_enemy_position.x < 1500)
		{
			speed.x = max_speed * 3;
			speed.y = -max_speed;
		}
		else if(cur_enemy_position.x < 750  && cur_enemy_position.x > 0)
		{
			speed.x = -max_speed * 3;
			speed.y = -max_speed;
		}
		else
		{
			speed.x = 0;
			speed.y = 0;
		}
	}

	//
	// This function proveraet touch li vilka hero
	//
	bool collide(sf::Vector2f hero_position)
	{
		sf::Vector2f cur_enemy_position = sprite.getPosition();

		if(	cur_enemy_position.x < hero_position.x + 20 &&
			cur_enemy_position.x > hero_position.x - 20 &&
			cur_enemy_position.y < hero_position.y + 20 &&
			cur_enemy_position.y > hero_position.y - 10)
			return true;

		return false;
	}
};


//
// default enemy
//
class enemy : public game_obj
{
	public:

	//class my_vector<int> speed;
	//class my_vector<int> size;

	//bool is_alive;

	int hp;
	int max_hp;
	int max_speed;
	
	//c_animation dead_animation;

	//sf::Sprite sprite;

	enemy()
	{
		hp = 3;
		max_hp = 3;
		max_speed = 4;
		size.x = 100;
		size.y = 100;

		is_alive = false;
	}

	// FUNCTIONS

	virtual void move(void) override
	{
		printf("enemy_move\n");

		if(is_alive == true)
		{
			printf("enemy_move 1\n");
			sprite.move(speed.x, speed.y);
			printf("enemy_move 2\n");
		}
	}

	virtual void draw(void) override
	{
		if(is_alive == true)
			Pwindow->draw(sprite);
	}
};


//!
//! NT This class realise heals
//!
class heals
{
	public:

	int hp_heal;
	sf::Sprite sprite;
	bool is_alive;

	sf::Vector2f position;

	heals()
	{
		hp_heal = rand() % 2 + 1;
		is_alive = false;
	}
};


//!
//! Draw heals
//!
void heals_draw(class heals *heal_massive, int max_of_heals)
{
	int cur_heal = 0;

	while(cur_heal != max_of_heals)
	{
		if(heal_massive[cur_heal].is_alive == true)
		{
			heal_massive[cur_heal].sprite.rotate(-2);
			Pwindow->draw(heal_massive[cur_heal].sprite);
		}

		cur_heal++;
	}
}


//
// Eat heals
//
void is_heal_use(class hero *main_hero, class heals *heal_massive, int max_of_heals)
{
	int cur_heal = 0;
	sf::FloatRect cur_hero_border = main_hero->sprite.getGlobalBounds();
	sf::FloatRect cur_heal_border;

	while(cur_heal != max_of_heals)
	{
		cur_heal_border = heal_massive[cur_heal].sprite.getGlobalBounds();

		if(heal_massive[cur_heal].is_alive == true && cur_hero_border.intersects(cur_heal_border))
		{
			heal_massive[cur_heal].is_alive = false;
			main_hero->hp = heal_massive[cur_heal].hp_heal + main_hero->hp;

			if(main_hero->hp > main_hero->max_hp)
				main_hero->hp = main_hero->max_hp;
		}

		cur_heal++;
	}
}


//
// This function realize enemys speed
//
void enemys_set_speed(class enemy* e_massive, int max_of_enemys, sf::Vector2f hero_position)
{
	int cur_enemy = 0;
	sf::Vector2f cur_enemy_position;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == true)
		{
			cur_enemy_position = e_massive[cur_enemy].sprite.getPosition();

			if((int)cur_enemy_position.x > (int)hero_position.x + e_massive[cur_enemy].max_speed * 2)
			{
				e_massive[cur_enemy].speed.x = -e_massive[cur_enemy].max_speed; 
				e_massive[cur_enemy].speed.y = 0;
			}
			else if((int)cur_enemy_position.x < (int)hero_position.x - e_massive[cur_enemy].max_speed * 2)
			{
				e_massive[cur_enemy].speed.x = e_massive[cur_enemy].max_speed; 
				e_massive[cur_enemy].speed.y = 0;
			}
			else if((int)cur_enemy_position.y > (int)hero_position.y + e_massive[cur_enemy].max_speed * 2)
			{
				e_massive[cur_enemy].speed.y = -e_massive[cur_enemy].max_speed; 
				e_massive[cur_enemy].speed.x = 0;
			}
			else if((int)cur_enemy_position.y < (int)hero_position.y - e_massive[cur_enemy].max_speed * 2)
			{
				e_massive[cur_enemy].speed.y = e_massive[cur_enemy].max_speed; 
				e_massive[cur_enemy].speed.x = 0;
			}
		}
		cur_enemy++;
	}
}


//
// This function realize mob spawn
//
void mob_spawn(class enemy* e_massive, int max_of_enemys, sf::Time cur_time)
{
	int cur_enemy = 0;
	int i_time = cur_time.asMilliseconds();
	i_time = 0;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == false)
		{
			e_massive[cur_enemy].hp = 3;
			e_massive[cur_enemy].is_alive = true;

			if(i_time % 4 == 0)
				e_massive[cur_enemy].sprite.setPosition(700 , -100);
			else if(i_time % 4 == 1)
				e_massive[cur_enemy].sprite.setPosition(700 , 1000);
			else if(i_time % 4 == 2)
				e_massive[cur_enemy].sprite.setPosition(-100 , 450);
			else if(i_time % 4 == 3)
				e_massive[cur_enemy].sprite.setPosition(1600 , 450);


		}

		i_time++;

		cur_enemy++;
	}
}


//
// This function rotate enemy
//
void enemy_rotation(class enemy* e_massive, int max_of_enemys)
{
	int cur_enemy = 0;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == true)
		{
			if(e_massive[cur_enemy].speed.x > 0)
			{
				e_massive[cur_enemy].sprite.setScale(-1, 1);

				if(e_massive[cur_enemy].sprite.getRotation() != 0) 
					e_massive[cur_enemy].sprite.setRotation(0);
			}
			else if(e_massive[cur_enemy].speed.x < 0)
			{
				e_massive[cur_enemy].sprite.setScale( 1 , 1);

				if(e_massive[cur_enemy].sprite.getRotation() != 0) 
					e_massive[cur_enemy].sprite.setRotation(0);
			}
			else if(e_massive[cur_enemy].speed.y > 0)
				e_massive[cur_enemy].sprite.setRotation(270);
			else if(e_massive[cur_enemy].speed.y < 0)
				e_massive[cur_enemy].sprite.setRotation(90);
		}

		cur_enemy++;
	}
}


//==============================================================================
//!
//! This function realise player and enemy collicion
//!
//==============================================================================
void player_hit(class hero *cur_hero, class enemy* e_massive, int max_of_enemys, sf::Time cur_time)
{
	int cur_enemy = 0;

	sf::FloatRect cur_enemy_border;
	sf::FloatRect cur_hero_border = cur_hero->sprite.getGlobalBounds();

	if(cur_time - cur_hero->last_damade_time > cur_hero->damage_cooldown)
	{
	
		while(cur_enemy != max_of_enemys)
		{
			cur_enemy_border = e_massive[cur_enemy].sprite.getGlobalBounds();

			if(e_massive[cur_enemy].is_alive == true && cur_enemy_border.intersects(cur_hero_border) && (cur_time - cur_hero->last_damade_time > cur_hero->damage_cooldown))
			{
				e_massive[cur_enemy].is_alive = false;
				e_massive[cur_enemy].hp = -1;
				cur_hero->hp--;
				cur_hero->last_damade_time = cur_time;
				return;
			}
	
			cur_enemy++;
		}
	}
}




//===============================================================================
//!
//! This function kill hero 
//!
//===============================================================================
bool is_hero_alive(class hero *cur_hero)
{
	if(cur_hero->hp <= 0)
		return false;
	else
		return true;
}

//===============================================================================
//
// Find empty heal
//
//===============================================================================
class heals *heal_finder(class heals *heal_massive, int max_of_heals)
{
	int heal_num = 0;

	while(heal_num != max_of_heals)
	{
		if(heal_massive[heal_num].is_alive == false)
		{
			//heal_massive[heal_num].is_alive = true;
			heal_massive[heal_num].hp_heal = rand() % 2 + 1;
			return &heal_massive[heal_num];
		}

		heal_num++;
	}

	return NULL;
}



//===============================================================================
//!
//! This function start_dead animation && kills enemy, if it hp < 0
//!
//! @param[in] class enemy* e_massive - pointer on enemys massive
//! @param[in] int max_of_enemys - max elements of enemys massive
//!
//===============================================================================
void kill_dead_enemys(class enemy* e_massive, int max_of_enemys, class heals *heal_massive, int max_of_heals)
{
	int cur_enemy = 0;
	int is_heal = 0;
	class heals *cur_heal = NULL;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].hp <= 0)
		{
			e_massive[cur_enemy].is_alive = false;
			is_heal = rand() % 2 + 1;

			if(is_heal == 1)
			{
				cur_heal = heal_finder(heal_massive, max_of_heals);

				if(cur_heal != NULL)
				{
					cur_heal->position = e_massive[cur_enemy].sprite.getPosition();
					if((20 <= cur_heal->position.x && cur_heal->position.x <= 1500 - 20) &&
						(20 <= cur_heal->position.y && cur_heal->position.y <= 900 - 20))
					{					
						cur_heal->sprite.setPosition(cur_heal->position.x, cur_heal->position.y);
						cur_heal->is_alive = true;
					}
					Kill_counter++;
				}
			}
		}
		cur_enemy++;
	}
}














