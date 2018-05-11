
//=======================================================================
//!
//! This library realise bullets & bullets_function
//!
//! USE SFML!!!
//!
//=======================================================================


class bullet : public game_obj
{
	public:

	//class my_vector<int> speed;
	//class my_vector<int> size;

	//bool is_alive;

	int damage;
	
	bool is_enemy_bullet;

	//sf::Sprite sprite;		
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

	virtual void move(void) override
	{
		printf("bullet_draw 1\n");
		sf::Time cur_time = Pclock->getElapsedTime();

		if(is_alive == true && (cur_time - time_of_born > time_of_life))
			is_alive = false;

		if(is_alive == true)
		{
			sprite.move(speed.x, speed.y);
			if(is_enemy_bullet == false)
				sprite.rotate(7);
		}
	}

	virtual void draw(void) override
	{
		if(is_alive == true)
			Pwindow->draw(sprite);
	}
};


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

			if(b_massive[cur_bullet].is_alive == true && 
			   cur_enemy_border.intersects(cur_bullet_border) &&
			   e_massive[cur_enemy].is_alive == true)
			{
				b_massive[cur_bullet].is_alive = false;
				b_massive[cur_bullet].sprite.setPosition(-100, -100);
				e_massive[cur_enemy].hp = e_massive[cur_enemy].hp - b_massive[cur_bullet].damage;
			}
			cur_bullet++;
		}

		cur_enemy++;
	}
}

void is_hero_shooted(class hero *cur_hero, class bullet* b_massive, int max_of_bullets)
{
	int i = 0;
	sf::FloatRect cur_border;
	sf::FloatRect cur_bullet_border;

	cur_border = cur_hero->sprite.getGlobalBounds();

	while(i != max_of_bullets)
	{
		if(b_massive[i].is_alive == true && b_massive[i].is_enemy_bullet == true)
		{
			cur_bullet_border = b_massive[i].sprite.getGlobalBounds();
				
			if(cur_border.intersects(cur_bullet_border))
			{
				b_massive[i].is_alive = false;
				b_massive[i].sprite.setPosition(-100, -100);
				cur_hero->hp--;
			}
		}
		i++;
	}
}








