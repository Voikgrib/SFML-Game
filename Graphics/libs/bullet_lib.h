
//=======================================================================
//!
//! This library realise bullets & bullets_function
//!
//! USE SFML!!!
//!
//=======================================================================


class bullet
{
	public:

	class my_vector<int> speed;
	class my_vector<int> size;

	int damage;
	

	bool is_enemy_bullet;
	bool is_alive;

	sf::Sprite sprite;		
	sf::Time time_of_born;  
	sf::Time time_of_life;

	  //=============//
	 // Consrtuctor //
	//=============//

	bullet()
	{
		size.x = 20;
		size.y = 20;
		damage = 1;

		time_of_life = sf::seconds(5); // Second

		is_alive = false;

		//printf("Bullet construct (no arg)\n");
	}


	  //===============//
	 // Deconsrtuctor //
	//===============//

	~bullet()
	{
		is_alive = false;
	}
	
	  //==========//
	 // Functons //
	//==========//

};


//============================================================================
//!
//! This function draw every alive bullet
//!
//! @param[in] class bullet* b_massive - pointer on bullet massive
//! @param[in] int max_of_bullets - max elements of bullet massive
//!
//============================================================================
void bullet_draw(class bullet* b_massive, int max_of_bullets)
{
	int cur_bullet = 0;

	while(cur_bullet != max_of_bullets)
	{
		if(b_massive[cur_bullet].is_alive == true)
			{
				 Pwindow->draw(b_massive[cur_bullet].sprite);
			}
	
		cur_bullet++;
	}
}

//============================================================================
//!
//! This function move every alive bullet and destroy every old bullet
//!
//! @param[in] class bullet* b_massive - pointer on bullet massive
//! @param[in] int max_of_bullets - max elements of bullet massive
//! @param[in] sf::Time cur_time - current time (needs to find old bullet)
//!
//============================================================================
void bullet_move(class bullet* b_massive, int max_of_bullets, sf::Time cur_time)
{
	int cur_bullet = 0;

	while(cur_bullet != max_of_bullets)
	{
		if(b_massive[cur_bullet].is_alive == true && (cur_time - b_massive[cur_bullet].time_of_born > b_massive[cur_bullet].time_of_life))
			b_massive[cur_bullet].is_alive = false;

		if(b_massive[cur_bullet].is_alive == true)
		{
			b_massive[cur_bullet].sprite.move(b_massive[cur_bullet].speed.x, b_massive[cur_bullet].speed.y);
			b_massive[cur_bullet].sprite.rotate(7);
		}

		cur_bullet++;
	}
}

//============================================================================
//!
//! This function find empty (not usng) bullet
//!
//! @param[in] class bullet* b_massive - pointer on bullet massive
//! @param[in] int max_of_bullets - max elements of bullet massive
//!
//============================================================================
class bullet *bullet_finder(class bullet* b_massive, int max_of_bullets)
{
	int cur_bullet = 0;

	while(cur_bullet != max_of_bullets)
	{
		if(b_massive[cur_bullet].is_alive == false)	
		{
			b_massive[cur_bullet].is_alive = true;
			return &b_massive[cur_bullet];
		}
	
		cur_bullet++;
	}

	return NULL;
}

//===============================================================================
//!
//! This function check does borders of some bullet cross enemy borders 
//!
//! @param[in] class bullet* b_massive - pointer on bullet massive
//! @param[in] int max_of_bullets - max elements of bullet massive
//! @param[in] class enemy* e_massive - pointer on enemys massive
//! @param[in] int max_of_enemys - max elements of enemys massive
//!
//===============================================================================
bool is_bullet_hit(class bullet* b_massive, int max_of_bullets, class enemy* e_massive, int max_of_enemys)
{
	int cur_enemy = 0;
	int cur_bullet = 0;

	sf::FloatRect cur_enemy_border;
	sf::FloatRect cur_bullet_border;

	while(cur_enemy != max_of_enemys)
	{
		cur_bullet = 0;

		while(cur_bullet != max_of_bullets)
		{
			cur_bullet_border = b_massive[cur_bullet].sprite.getGlobalBounds();
			cur_enemy_border = e_massive[cur_enemy].sprite.getGlobalBounds();

			if(cur_enemy_border.intersects(cur_bullet_border) && e_massive[cur_enemy].is_alive == true && b_massive[cur_bullet].is_alive == true)
			{
				b_massive[cur_bullet].is_alive = false;
				e_massive[cur_enemy].hp = e_massive[cur_enemy].hp - b_massive[cur_bullet].damage;
			}
			cur_bullet++;
		}

		cur_enemy++;
	}
}








