
//=========================================================================
//!
//! This lib realize redactor on my asm, which be implimented in game
//!
//=========================================================================

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF MAGIC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#define IF_LETTER(SFML_LETTER, C_LETTER)\
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::SFML_LETTER) && last_time + cooldown <= Pclock->getElapsedTime())\
		{\
			buffer[cur_len++] = C_LETTER;\
			last_time = Pclock->getElapsedTime();\
		}\
			

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF MAGIC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


//!-------------------------------------------------------------------------------
//!
//! This function get size of reading file
//!
//! @param[in] FILE *prog - file which we worked
//!
//! @param[out] size of file
//!
//!-------------------------------------------------------------------------------
long int get_file_size(FILE *prog)
{
    long int size_of_prog = 0;

    const int zero = 0;

    fseek(prog, zero, SEEK_END);
    size_of_prog = ftell(prog);

    return size_of_prog;
}

//!-------------------------------------------------------------------------------
//!
//! This function reading file
//!
//! @param[in] FILE *prog - file which we worked
//! @param[in] long int size_of_prog - size of file
//! @param[in] char *my_buff - buffer, which we worked
//!
//!-------------------------------------------------------------------------------
void file_read(FILE *prog, long int size_of_prog, char *my_buff)
{
    const int zero = 0;

    fseek(prog, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_prog, prog);
}

//=========================================================================
//!
//! This function realize main body of redactor
//!
//! Return 0 - if okey & load game, -num if error, +num if okey end end
//!
//=========================================================================
int redactor_main_body(void)
{
	FILE *old_file = fopen("prog.txt","r");

	int size_of_old_prog = get_file_size(old_file);
	int max_buff_size = 1000 + size_of_old_prog;
	int cur_len = size_of_old_prog;

	char *buffer = new char [max_buff_size];
	char *old_buffer = new char [size_of_old_prog];

	file_read(old_file, size_of_old_prog, old_buffer);
	file_read(old_file, size_of_old_prog, buffer);

	bool is_end_of_redactor = false;

	sf::Time cooldown = sf::seconds(0.1f);
	sf::Time last_time = sf::seconds(0);

	sf::Text old_text;
	sf::Text new_text;
	sf::Text old_text_header;
	sf::Text new_text_header;

	sf::Font font;
	font.loadFromFile("prog_part/ARIAL.TTF");

	fclose(old_file);

	new_text_header.setString("New code\t press Escape to quit");
	new_text_header.setFont(font);
	new_text_header.setStyle(sf::Text::Bold | sf::Text::Underlined);
	new_text_header.setColor(sf::Color::Red);
	new_text_header.setCharacterSize(24);
	new_text_header.setOrigin(0,0);
	new_text_header.setPosition(200, 50);

	old_text_header.setString("Old code");
	old_text_header.setFont(font);
	old_text_header.setStyle(sf::Text::Bold | sf::Text::Underlined);
	old_text_header.setColor(sf::Color::Red);
	old_text_header.setCharacterSize(24);
	old_text_header.setOrigin(0,0);
	old_text_header.setPosition(1000, 50);

	old_text.setString(old_buffer);
	old_text.setFont(font);
	old_text.setCharacterSize(16);
	old_text.setOrigin(0,0);
	old_text.setPosition(800, 100);
	
	new_text.setString(buffer);
	new_text.setFont(font);
	new_text.setCharacterSize(16);
	new_text.setOrigin(0,0);
	new_text.setPosition(50, 100);

	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
        sf::Event event;
        while (Pwindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                Pwindow->close();
				//printf("> It is not error, it is costil! C-:\n");
				return 1;
			}
        }

		//cur_symbol = getchar();


		//cur_time = Pclock->getElapsedTime();

		#include"big_define_lib.h"

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && last_time + cooldown <= Pclock->getElapsedTime())
		{
			buffer[cur_len--] = 0;
			last_time = Pclock->getElapsedTime();
		}

		new_text.setString(buffer);

		// redactor sycle is here
		// ifs & so on

		// Draw here
		Pwindow->clear();
		Pwindow->draw(new_text_header);
		Pwindow->draw(old_text_header);
		Pwindow->draw(new_text);
		Pwindow->draw(old_text);
		Pwindow->display();
	}

	// Compiller 

	buffer[cur_len] = 0;

	old_file = fopen("prog.txt","w");
	fprintf(old_file, "%s", buffer);
	fclose(old_file);
	
	//system("cd prog_part/");
	system("./Stack_compiler");
	system("./compiler");
	system("./asm_prog");

	// system("");
	// Error worker

	delete [] buffer; 
	delete [] old_buffer;

	return 0;
}




