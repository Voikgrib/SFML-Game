
//======================================================================
//!
//! This lib realize hero & hero functions
//!
//======================================================================


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
	sf::Time shoot_cooldown;
	int speed;
	int bullet_speed;
	int hp;
	int max_hp;

	//=============//
	// Consrtuctor //
	//=============//

	hero()
	{
		size.x = 100;
		size.y = 100;
		position.x = 200;
		position.y = 200;
		speed = 5;
		bullet_speed = 10;
		hp = 5;
		max_hp = 5;
		shoot_cooldown = sf::seconds(0.2f);

		printf("Hero inisialized\n");
		texture.setSmooth(true);
		texture.loadFromFile("test_pizza.png");
		sprite.setTexture(texture);
		sprite.setPosition(position.x, position.y);
		sprite.setOrigin(size.x/2, size.y/2);
	}

	//==========//
	// Functons //
	//==========//
	

};



