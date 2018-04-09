
//=======================================================================
//!
//! This library realise enemy class and so on
//!
//=======================================================================

class enemy
{
	public:

	bool is_alive;

	int hp;
	int max_hp;
	int max_speed;

	class my_vector<int> speed;
	class my_vector<int> size;

	sf::Sprite sprite;

	enemy()
	{
		hp = 3;
		max_hp = 3;
		max_speed = 3;
		size.x = 100;
		size.y = 100;

		is_alive = false;
	}

};


//
// This function realize enemys speed !!!!!!!
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
// This function realize enemy movement
//
void enemy_movement(class enemy* e_massive, int max_of_enemys)
{
	int cur_enemy = 0;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == true)
		{
			 e_massive[cur_enemy].sprite.move(e_massive[cur_enemy].speed.x, e_massive[cur_enemy].speed.y);
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
			Pwindow->draw(e_massive[cur_enemy].sprite);

		cur_enemy++;
	}
}


//===============================================================================
//!
//! This function kills enemy, if it hp < 0
//!
//! @param[in] class enemy* e_massive - pointer on enemys massive
//! @param[in] int max_of_enemys - max elements of enemys massive
//!
//===============================================================================
void kill_dead_enemys(class enemy* e_massive, int max_of_enemys)
{
	int cur_enemy = 0;

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].hp <= 0)
			e_massive[cur_enemy].is_alive = false;

		cur_enemy++;
	}
}
