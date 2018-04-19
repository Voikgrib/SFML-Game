
//=================================================================
//!
//! This lib contain HUD elements and HUD functions
//!
//=================================================================

// NT NT NT NT NT

void hp_drawer(sf::Sprite hp_sprite, class hero *main_hero)
{

	while(cur_enemy != max_of_enemys)
	{
		if(e_massive[cur_enemy].is_alive == true)
			Pwindow->draw(hp_sprite);

		cur_enemy++;
	}

}
