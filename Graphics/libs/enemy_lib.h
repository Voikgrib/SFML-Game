
//=======================================================================
//!
//! This library realise enemy class and so on
//!
//=======================================================================

class enemy : public game_obj
{
	public:

	//class my_vector<int> speed;
	//class my_vector<int> size;

	//bool is_alive;

	int hp;
	int max_hp;
	int max_speed;

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
//! NT Draw heals
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
				e_massive[cur_enemy].sprite.setPosition(700 , 100);
			else if(i_time % 4 == 1)
				e_massive[cur_enemy].sprite.setPosition(700 , 800);
			else if(i_time % 4 == 2)
				e_massive[cur_enemy].sprite.setPosition(300 , 450);
			else if(i_time % 4 == 3)
				e_massive[cur_enemy].sprite.setPosition(1100 , 450);


		}

		i_time++;

		cur_enemy++;
	}
}


//
// This function realize enemy movement
//
void enemy_movement(class enemy* e_massive, int max_of_enemys)
{
	int cur_enemy = 0;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == true)
		{
			 e_massive[cur_enemy].move();
		}

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
				e_massive[cur_enemy].sprite.setRotation(180);
			else if(e_massive[cur_enemy].speed.x < 0)
				e_massive[cur_enemy].sprite.setRotation(0);
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
//! This function dispay alives enemys
//!
//! @param[in] class enemy* e_massive - pointer on enemys massive
//! @param[in] int max_of_enemys - max elements of enemys massive
//!
//===============================================================================
void enemys_draw(class enemy* e_massive, int max_of_enemys)
{
	int cur_enemy = 0;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == true)
			e_massive[cur_enemy].draw();

		cur_enemy++;
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
// Find empty heal 			NT
//
//===============================================================================
class heals *heal_finder(class heals *heal_massive, int max_of_heals)
{
	int heal_num = 0;

	while(heal_num != max_of_heals)
	{
		if(heal_massive[heal_num].is_alive == false)
		{
			heal_massive[heal_num].is_alive = true;
			heal_massive[heal_num].hp_heal = rand() % 2 + 1;
			return &heal_massive[heal_num];
		}

		heal_num++;
	}

	return NULL;
}



//===============================================================================
//!
//! This function kills enemy, if it hp < 0
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
					cur_heal->sprite.setPosition(cur_heal->position.x, cur_heal->position.y);
					cur_heal->is_alive = true;
				}
			}
		}
		cur_enemy++;
	}
}














