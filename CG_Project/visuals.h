struct point 
{
	float x; 
	float y; 
	float z; 
};

struct face
{
	int vtx[3];
};

struct duck
{
	point obj_points[427];
	face obj_faces[824];
    int vertices;
	int faces;
};

struct balloon
{
	point obj_points[447];
	face obj_faces[1398];
    int vertices;
	int faces;
};

//float duckcol[]={1.0,1.0,0.0};

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void cdr();

void Keyboard(unsigned char,int,int);

void SpecialKeyboard(int,int,int);

void ReadFile(duck *d,balloon *b);

void DisplayDuck(duck b);

void DisplayBalloon(balloon b);

