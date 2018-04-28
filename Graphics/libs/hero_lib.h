
//======================================================================
//!
//! This lib realize hero & hero functions
//!
//======================================================================

#define MAX_HP	10

//-----------------------------------------------------------------
//!
//!	This class realise hero class
//!
//-----------------------------------------------------------------
class hero
{
	public:

	class my_vector<int> size;
	class my_vector<int> position;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture hp_texture_one;
	sf::Texture hp_texture_two;
	sf::Sprite hp_sprite_one;
	sf::Sprite hp_sprite_two[MAX_HP];
	sf::Time shoot_cooldown;
	sf::Time damage_cooldown;
	sf::Time last_damade_time;
	int speed;
	int bullet_speed;
	int hp;
	int max_hp;
	bool is_alive;

	//=============//
	// Consrtuctor //
	//=============//

	hero()
	{
		is_alive = true;
		size.x = 100;
		size.y = 100;
		position.x = 700;
		position.y = 450;
		speed = 6;
		bullet_speed = 10;
		hp = 7;
		max_hp = MAX_HP;
		shoot_cooldown = sf::seconds(0.2f);
		damage_cooldown = sf::seconds(1.2f);

		printf("Hero inisialized\n");
		texture.setSmooth(true);
		if(!texture.loadFromFile("test_pizza.png"))
			throw;

		sprite.setTexture(texture);
		sprite.setPosition(position.x, position.y);
		sprite.setOrigin(size.x/2, size.y/2);
		if(!hp_texture_one.loadFromFile("hp_one.png"))
			throw;

		hp_sprite_one.setTexture(hp_texture_one);
		if(!hp_texture_two.loadFromFile("hp_two.png"))
			throw;
		

		int i = 0;

		while(i != max_hp)
		{
			hp_sprite_two[i].setTexture(hp_texture_two);
			hp_sprite_two[i].setPosition(10, 40 + 40 * i);

			i++;
		}
	}

	//~hero()
	//{
	//	delete [] hp_sprite_two;
	//}

	//==========//
	// Functons //
	//==========//
	

};


//
//! This function check is pizza on plane?
//
bool is_pizza_not_on_plane(sf::Vector2f hero_position)
{
	if((hero_position.x > 1200 || hero_position.x < 300) && (hero_position.y > 200 && hero_position.y < 700))
		return true;
	else if((hero_position.x > 1100 || hero_position.x < 400) && (hero_position.y < 200 || hero_position.y > 700))
		return true;


	return false;
}


//------------------------------------------------------------------------
//!
//! This function draws hp
//!
//------------------------------------------------------------------------
void hp_draw(class hero cur_hero)
{
	int cur_hp = 0;
	int cur_counter = 0;

	if(cur_hero.hp > 0)
	{
		while(cur_hp != (cur_hero.hp / 2))
		{
			Pwindow->draw(cur_hero.hp_sprite_two[cur_hp]);
	
			cur_hp++;
			cur_counter++;
			cur_counter++;
		}
	
		if(cur_counter != cur_hero.hp)
		{
			cur_hp++;
			cur_hero.hp_sprite_one.setPosition(10, 40 * cur_hp);
			Pwindow->draw(cur_hero.hp_sprite_one);
		}
	}	
}







