
//=============================================================
//!
//! This lib realise main menu & others menu
//!
//=============================================================

class c_menu_part
{
	public:

	sf::Sprite cur_text;
	bool is_close_button;
};

class c_menu
{
	public:

	class c_animation *backgrownd_anim;
	class c_animation *pos_pointer_anim;	
	class c_menu_part *part_massive;

	sf::Sprite backgrownd_sprite;
	sf::Sprite pos_pointer_sprite;

	int active_part;
	int size;

	  //
	 // Constructor & Deconstructor
	//
	// b_anim_amount - 
	// p_anim_amount - 
	// menu_part_amount - size of menu
	// backgrownd_anim_input - pointer on backrownd animation
	// pos_pointer_anim_input - pointer on arrow animation

	c_menu(sf::Sprite *sprite_massive, int menu_part_amount, class c_animation *backgrownd_anim_input, class c_animation *pos_pointer_anim_input)
	{
		//backgrownd_anim = backgrownd_anim_input;  		// AXTUNG need ceate animations before construct the menu
		pos_pointer_anim = pos_pointer_anim_input;

		size = menu_part_amount;
		active_part = 0;
		part_massive = new c_menu_part [size];

		int i = 0;

		while(i != size)
		{
			part_massive[i].is_close_button = false;
			part_massive[i].cur_text = sprite_massive[i];
			i++;
		}

		part_massive[size - 1].is_close_button = true;
	}

	~c_menu()
	{
		size = -1;

		delete [] part_massive;
	}

	  //
	 // Functions NT
	//
	// Need func pointer here, it must take (int) num of cur_menu poz & contain inside 100500 switches
	int menu_call(int (*cur_menu_func)(int))
	{
		bool is_out_pressed = false;
		int ret = 0;

		sf::Vector2f v_active_pos;
		//sf::Vector2f v_pointer_size;
		int i = 0;

		Pwindow->clear();

		while(is_out_pressed == false)
		{
	        sf::Event event;
	        while (Pwindow->pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
				{
	                Pwindow->close();
					//printf("> It is not error, it is costil! C-:\n");
					return -1;
				}
	        }


			i = 0;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))		 	// Move down
			{
				if(active_part != size - 1)
					active_part++;
				else
					active_part = 0;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 	// Move up
			{
				if(active_part != 0)
					active_part--;
				else
					active_part = size - 1;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if(part_massive[active_part].is_close_button == false)
					return cur_menu_func(active_part);
				else
					return -1;
			}
			

			// Plase arrows on text of menu
			// v_pointer_size = pos_pointer_sprite.getPosition();
			v_active_pos = part_massive[active_part].cur_text.getPosition();
			v_active_pos.x = v_active_pos.x - 30;								// Max x size of pointer = 30 pixels
			pos_pointer_sprite.setTexture(pos_pointer_anim->get_cur_texture());
			pos_pointer_sprite.setPosition(v_active_pos.x, v_active_pos.y);

			// Animation part
			//backgrownd_anim->a_run();
			pos_pointer_anim->a_run(Pclock->getElapsedTime());

			Pwindow->clear();		// Draw menu & so on here
			//Pwindow->draw(backgrownd_sprite);
			while(i != size)
				Pwindow->draw(part_massive[i++].cur_text);
			Pwindow->draw(pos_pointer_sprite);
			Pwindow->display();
		}
	}

	
};




