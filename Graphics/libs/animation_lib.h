
class c_frame
{
	public:

	sf::Texture texture;
	sf::Time frame_delay;
};

class c_animation
{
	public:

	class c_frame* frame_massive;
	sf::Time last_frame_time;
	int cur_frame;
	int size;

	//
	// Constructor & deconstructor
	//
	c_animation(int new_size)
	{
		frame_massive = new c_frame [new_size];
		size = new_size;
		last_frame_time = sf::seconds(0);
		cur_frame = 0;
	}

	~c_animation()
	{
		size = -1;
		cur_frame = -1;
		delete [] frame_massive;
	}

	//
	// Functions
	//
	void a_run(sf::Time cur_time)
	{
		if(cur_time >= last_frame_time + frame_massive[cur_frame].frame_delay)
		{
			cur_frame++;

			if(cur_frame == size)
				cur_frame = 0;

			last_frame_time = cur_time;
		}
	}

	sf::Texture &get_cur_texture(void)
	{
		return frame_massive[cur_frame].texture;
	}
};



