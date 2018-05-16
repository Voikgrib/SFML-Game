
//===============================================================
//!
//! This library realize boss class and boss functions
//!
//===============================================================
class c_boss : public game_obj
{
	public:

	class bullet *m_bull_1;
	class bullet *m_bull_2;

	sf::Time cooldown;
	sf::Time last_shoot_time;

	sf::Texture all_texture;
	sf::Texture texture;

	sf::Sprite hp_sprite;
	sf::Sprite hp_bar_sprite;

	//c_animation *sec_bull_atimation(4);

	int max_1;
	int max_2;
	int hp;
	int max_hp;
	int max_speed;

	//
	// Constructor
	//

	c_boss(int max_of_bullets_1, int max_of_bullets_2)
	{
		max_1 = max_of_bullets_1;
		max_2 = max_of_bullets_2;
		m_bull_1 = new bullet [max_1];
		m_bull_2 = new bullet [max_2]; // NI
		//sec_bull_atimation = new c_animation [max_2];


		speed.x = 0;
		speed.y = 0;
		max_speed = 2;

		cooldown = sf::seconds(0.7f);
		last_shoot_time = sf::seconds(0);

		max_hp = 200;
		hp = 200;
		is_alive = true;

		all_texture.loadFromFile("boss_hud.png");

		int i = 0;

		while(i != max_1)
		{
			m_bull_1[i].is_enemy_bullet = true;
			m_bull_1[i].is_alive = false;
			m_bull_1[i].sprite.setTexture(all_texture);
			m_bull_1[i].sprite.setTextureRect(sf::IntRect(3, 25, 12, 74));
			m_bull_1[i].sprite.setScale(1.5, 1.5);
			m_bull_1[i].size.x = 12 * 1.5;
			m_bull_1[i].size.y = 74 * 1.5;

			i++;
		}

		i = 0;

		while(i != max_2)
		{
			m_bull_2[i].is_enemy_bullet = true;
			m_bull_2[i].is_alive = false;
			m_bull_2[i].sprite.setTexture(all_texture);
			m_bull_2[i].sprite.setTextureRect(sf::IntRect(21, 26, 32, 13));
			m_bull_2[i].sprite.setScale(1.5, 1.5);
			m_bull_2[i].size.x = 32 * 1.5;
			m_bull_2[i].size.y = 13 * 1.5;
			
			//sec_bull_atimation[i].frame_massive[1].texture.setTexture(all_texture);
			//sec_bull_atimation[i].frame_massive[1].texture.setTextureRect.sf::IntRect(21, 26, 22, 13);
			

			i++;
		}

		i = 0;

		hp_bar_sprite.setTexture(all_texture);
		hp_bar_sprite.setTextureRect(sf::IntRect(0, 0, 100, 14)); // hp bar coords
		hp_sprite.setTexture(all_texture);
		hp_sprite.setTextureRect(sf::IntRect(0, 14, 100, 10));

		hp_bar_sprite.setOrigin(0, 7);
		hp_sprite.setOrigin(0, 5);
		hp_bar_sprite.setScale(4, 3);
		hp_sprite.setScale(4, 3);
		hp_bar_sprite.setPosition(500, 70);
		hp_sprite.setPosition(500, 70);

		texture.loadFromFile("boss.png");
		sprite.setTexture(texture);
		sprite.setPosition(500, 500);
		sprite.setOrigin(150, 100);
	}

	~c_boss()
	{
		delete [] m_bull_1;
		delete [] m_bull_2;
	}

	//
	// functions NI
	//
	void hud_draw(void)
	{
		hp_sprite.setTexture(all_texture);
		hp_sprite.setTextureRect(sf::IntRect(0, 14, hp / 2, 10));
		hp_sprite.setPosition(500, 70);

		Pwindow->draw(hp_sprite);
		Pwindow->draw(hp_bar_sprite);
	}

	void is_damage_get(class bullet* b_massive, int max_of_bullets)
	{
		int cur_bullet = 0;
		sf::FloatRect cur_border;
		sf::FloatRect cur_bullet_border;
		cur_border = sprite.getGlobalBounds();

		while(cur_bullet != max_of_bullets)
		{
			cur_bullet_border = b_massive[cur_bullet].sprite.getGlobalBounds();

			if(b_massive[cur_bullet].is_alive == true && 
			   cur_border.intersects(cur_bullet_border) &&
			   is_alive == true)
			{
				b_massive[cur_bullet].is_alive = false;
				b_massive[cur_bullet].sprite.setPosition(-100, -100);
				hp = hp - b_massive[cur_bullet].damage;
			}
			cur_bullet++;
		}
	}

	void super_intellect(class hero *cur_hero)
	{
		sf::Vector2f cur_position;
		sf::Vector2f hero_position;

		cur_position = sprite.getPosition();
		hero_position = cur_hero->sprite.getPosition();				// NEED 2 FAZES!
	
		if(hp >= max_hp / 2)
		{
			if((int)cur_position.x > (int)hero_position.x + max_speed * 2)
				speed.x = -max_speed; 
			if((int)cur_position.x < (int)hero_position.x - max_speed * 2)
				speed.x = max_speed; 
			if((int)cur_position.y > (int)hero_position.y + max_speed * 2)
				speed.y = -max_speed; 
			if((int)cur_position.y < (int)hero_position.y - max_speed * 2)
				speed.y = max_speed; 
		}
		else
		{
			speed.y = speed.y * 1.1;

			if((int)cur_position.x < 1300)
				speed.x = max_speed * 7;
			else
				speed.x = 0;

			if((int)cur_position.y < 100 && speed.y < 0)
				speed.y = max_speed * 4;
			else if((int)cur_position.y > 800 && speed.y > 0)
				speed.y = -max_speed * 4;
		}
	}

	void shooting(class hero *cur_hero)
	{
		sf::Vector2f attack_vector = cur_hero->sprite.getPosition() - sprite.getPosition();	// vector to hero
		class bullet *cur_bullet_1 = bullet_finder(m_bull_1, max_1);
		cur_bullet_1->is_alive = false;
		class bullet *cur_bullet_2 = bullet_finder(m_bull_2, max_2);
		cur_bullet_2->is_alive = false;

		int random = (rand() % 15) - 7;


		sf::Time cur_time = Pclock->getElapsedTime();
		sf::Vector2f cur_position;

		cur_position = sprite.getPosition();

		if(last_shoot_time + cooldown < cur_time && cur_bullet_1 != NULL && cur_bullet_2 != NULL)
		{
			cur_bullet_1->is_alive = true;
			cur_bullet_1->sprite.setRotation(-(atan(attack_vector.x / attack_vector.y) * 180.0f / 3.14f));
			cur_bullet_1->sprite.setPosition(cur_position.x, cur_position.y);
			last_shoot_time = cur_time;
			cur_bullet_1->speed.x = attack_vector.x / 35 + 1;
			cur_bullet_1->speed.y = attack_vector.y / 35 + 1;
			cur_bullet_1->time_of_born = cur_time;
			// NI need itit second massive of bullets
			if(hp <= max_hp / 2)
			{
				cur_bullet_2->is_alive = true;
				cur_bullet_2->sprite.setPosition(cur_position.x, cur_position.y);
				cur_bullet_2->speed.x = attack_vector.x / 35 + 1;
				cur_bullet_2->speed.y = attack_vector.y / 35 + random;
				cur_bullet_2->time_of_born = cur_time;			
			}
		}
	}

	//
	// virtual functions
	//

	virtual void move(void) override
	{
		if(is_alive == true)
		{
			printf("boss_move 1\n");
			sprite.move(speed.x, speed.y);
			printf("boss_move 2\n");
		}
	}

	virtual void draw(void) override
	{
		if(is_alive == true)
			Pwindow->draw(sprite);
	}
};



