
//
// This class realise parent game class 
//
class game_obj
{
	public:

	sf::Sprite sprite;
	
	class my_vector<int> speed;
	class my_vector<int> size;

	bool is_alive;
	
	virtual void move() = 0;
	virtual void draw() = 0;

};

class manager
{
	public:

	class game_obj** massive;
	int absolute_max;
	int maximum;

	  //==========================//
	 // Constructor & destructor //
	//==========================//

	manager()
	{
		printf("manager created! \n");
		maximum = 0;
		massive = new game_obj* [Max_obj];
		absolute_max = Max_obj;
	}

	~manager()
	{

		delete [] massive;

	}

	  //===========//
	 // Functions //
	//===========//

	
	void adder(void* new_elem, int size, unsigned long int size_of_type)
	{
		int i = maximum;
		unsigned long int copy = 0;

		if(absolute_max <= maximum + size)
		{
			printf("TOO MUCH OBJECTS!\n");
			assert(false);
		}
		
		while(copy != size)
		{
			massive[i] = (class game_obj*) (new_elem + (copy * size_of_type));


			copy++;
			i++;
		}

		maximum = maximum + copy;
	}

	void add(class game_obj* new_elem)
	{
		if(absolute_max <= maximum)
		{
			printf("TOO MUCH OBJECTS!\n");
			assert(false);
		}
		else
			massive[maximum++] = new_elem;
	}

	// Move & draw
	void run()
	{
		int cur_elem = 0;

		while(cur_elem != maximum)	
		{
			//printf("all_move	1\n");
			if(massive[cur_elem] != NULL)
			{
				//printf("all_move	1.1\n");
				//printf("cur_elem = %p\n", massive[cur_elem]);
				massive[cur_elem]->move();
				massive[cur_elem]->draw();
				//printf("all_move	1.2\n");			
			}

			//printf("all_move	2\n");

			cur_elem++;
		}

	}
};











