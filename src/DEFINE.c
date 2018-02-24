// let's define some stuff
#define PPU_CTRL		*((unsigned char*)0x2000)
#define PPU_MASK		*((unsigned char*)0x2001)
#define PPU_STATUS		*((unsigned char*)0x2002)
#define OAM_ADDRESS		*((unsigned char*)0x2003)
#define SCROLL			*((unsigned char*)0x2005)
#define PPU_ADDRESS		*((unsigned char*)0x2006)
#define PPU_DATA		*((unsigned char*)0x2007)
#define OAM_DMA			*((unsigned char*)0x4014)


#define RIGHT		0x01
#define LEFT		0x02
#define DOWN		0x04
#define UP			0x08
#define START		0x10
#define SELECT		0x20
#define B_BUTTON	0x40
#define A_BUTTON	0x80


//Globals
//our startup code initialized all values to zero
#pragma bss-name(push, "ZEROPAGE")
unsigned char NMI_flag;
unsigned char Frame_Count;
unsigned char index;
unsigned char spr_loop;
unsigned char boxloop;
unsigned char box_prepared;
unsigned char index4;
unsigned char X1;
unsigned char Y1;
unsigned char state;
unsigned char state4;
unsigned char joypad1;
unsigned char joypad1old;
unsigned char joypad1test; 
unsigned char joypad2; 
unsigned char joypad2old;
unsigned char joypad2test;
unsigned char new_background;
unsigned char screen_num;
unsigned char exit_dir;
unsigned char which_BGD;
const unsigned char * p_C_MAP; //Caddress is an int that points to a char
unsigned char X1_Right_Side;	//for collision test
unsigned char X1_Left_Side;
unsigned char Y1_Bottom;
unsigned char Y1_Top;
unsigned char corner;
unsigned char climb;
unsigned char frame;
unsigned char dir;
unsigned char level_loaded;
unsigned char game_state;
unsigned char game_mode;
unsigned char metaspritedata;
unsigned char sprite_state;
unsigned char paused;
unsigned char since_last_pause;
unsigned char sprn;
unsigned char title_music;
unsigned char friend_state;
unsigned char final_timer;
unsigned char Text_Position;
unsigned char end_timer;

#define NUM_ACTORS 15
unsigned char actor_on[NUM_ACTORS];      // for drawing object to screen
unsigned char actor_facing[NUM_ACTORS];  // direction: 0x00=right, 0x40=left
unsigned char actor_y[NUM_ACTORS];       // top side, if = 0 = off
unsigned char actor_x[NUM_ACTORS];       // left side
unsigned char actor_type[NUM_ACTORS];    // wait to start moves
unsigned char sprite_index[NUM_ACTORS];
unsigned char actor_extradata[NUM_ACTORS];
unsigned char actor_extradata2[NUM_ACTORS];
unsigned char actor_extradata3[NUM_ACTORS];

const unsigned char CIRCLEX[]={ 8, 8, 7, 7, 6, 4, 3, 2, 0,-2,-3,-4,-6,-7,-7,-8,-8,-8,-7,-7,-6,-4,-3,-2, 0, 2, 3, 4, 6, 7, 7, 8};
const unsigned char CIRCLEY[]={ 0, 2, 3, 4, 6, 7, 7, 8, 8, 8, 7, 7, 6, 4, 3, 2, 0,-2,-3,-4,-6,-7,-7,-8,-8,-8,-7,-7,-6,-4,-3,-2};

const unsigned char TITLE_PALETTE[]={
0x0f, 0x00, 0x20, 0x20,  0, 1, 0x21, 0x31,  0, 0, 0x20, 0x20,  0x00, 0x01, 0x11, 0x38,
0x00, 0x01, 0x11, 0x00,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 5, 0x15};

const unsigned char DAY_PALETTE[]={
0x0f, 0x16, 0x06, 0x2a,  0, 1, 0x21, 0x31,  0, 0, 0x10, 0x20,  0, 0x0a, 0x1a, 0x2a,
0x0f, 0x01, 0x11, 0x38,  0, 0x16, 0x06, 0x37,  0, 0x09, 0x19, 0x2a,  0, 0, 5, 0x15};

const unsigned char RED_PALETTE[]={
0x0f, 0x16, 0x06, 0x2a,  0, 6, 0x5, 0x15,  0, 0, 0x10, 0x20,  0, 0x0a, 0x1a, 0x2a,
0x0f, 0x01, 0x11, 0x38,  0, 0x16, 0x06, 0x37,  0, 0x09, 0x19, 0x2a,  0, 0, 5, 0x15};

const unsigned char SUNSET_PALETTE[]={
0x0f, 0x16, 0x06, 0x2a,  0, 0x16, 0x27, 0x37,  0, 0, 0x10, 0x20,  0, 0x0a, 0x1a, 0x2a,
0x0f, 0x01, 0x11, 0x38,  0, 0x16, 0x06, 0x37,  0, 0x09, 0x19, 0x2a,  0, 0, 5, 0x15};

const unsigned char NIGHT_PALETTE[]={
0x0f, 0x16, 0x06, 0x2a,  0, 0x0F, 0x03, 0x13,  0, 0, 0x10, 0x20,  0, 0x0a, 0x1a, 0x2a,
0x0f, 0x01, 0x11, 0x38,  0, 0x16, 0x06, 0x37,  0, 0x09, 0x19, 0x2a,  0, 0, 5, 0x15};

const unsigned char FINAL_PALETTE[]={
0x0f, 0x16, 0x06, 0x2a,  0, 0x0F, 0x03, 0x13,  0, 0x16, 0x06, 0x03,  0, 0x28, 0x18, 0x03,
0x0f, 0x01, 0x11, 0x38,  0, 0x28, 0x38, 0x0F,  0, 0x15, 0x38, 0x0F,  0x0F, 0x0F, 0x0F, 0x0F};

const unsigned char INTRO_PALETTE[]={
0x0f, 0x16, 0x06, 0x2a,  0, 1, 0x21, 0x31,  0, 0, 0x10, 0x20,  0, 0x0a, 0x1a, 0x2a,
0x0f, 0x01, 0x11, 0x38,  0, 0x28, 0x38, 0x0F,  0, 0x15, 0x38, 0x0F,  0x0F, 0x0F, 0x0F, 0x0F};

#pragma bss-name(push, "OAM")
unsigned char SPRITES[256];
//OAM equals ram addresses 200-2ff

#pragma bss-name(push, "MAP")
unsigned char C_MAP[256];
//MAP equals ram addresses 300-3ff, collision map, metatiles

const unsigned char exit_table[]={-1, 1, 2, 2, 3, 1, 1, 2, 2, 2, 1, 3, 3, 1, -1, -1, -1};
const unsigned char x_spawns[]={0x10, 0x10, 0x00, 0xA0, 0x10, 0xA0, 0x02, 0x02, 0xE0, 0x20, 0x10, 0x02, 0xB0, 0x40, 0x02, 0x68, 0x10};
const unsigned char y_spawns[]={0xC0, 0xC0, 0xA0, 0xD0, 0xC0, 0x02, 0x40, 0x50, 0xD0, 0xC0, 0xE0, 0x70, 0x02, 0x02, 0xB0, 0x70, 0xC0};

const unsigned char BAD_END_TEXT[]={
"   Try again on HARD MODE!! "};

const unsigned char GOOD_END_TEXT[]={
"  The adventure is now over."};

const unsigned char INTRO_TEXT[]={
" Haha! Your BEST FRIEND is"};

const unsigned char INTRO2_TEXT[]={
" at top of  the  MOUNTAIN!"};

const unsigned char MetaSprite_Y[] = {0, 0, 8, 8}; //relative y coordinates

const unsigned char MetaSprite_Tile[] = { //tile numbers
	2, 3, 0x12, 0x13, //right
	0, 1, 0x10, 0x11, //down
	6, 7, 0x16, 0x17, //left
	4, 5, 0x14, 0x15, //up
	8, 9, 0x18, 0x19, //fireball 1
	0x0a, 0x0b, 0x1a, 0x1b, //fireball 2
	0x0c, 0x0d, 0x1c, 0x1d, //fireball 3
	0x0e, 0x0f, 0x1e, 0x1f};//rope

enum {Going_Right, Going_Down, Going_Left, Going_Up};

const unsigned char Fireball_Tile[] = {
	8, 9, 0x18, 0x19, //fireball 1
	0x0a, 0x0b, 0x1a, 0x1b, //fireball 2
	0x0c, 0x0d, 0x1c, 0x1d//fireball 3
};

const unsigned char Fireball_Attrib[] = {1, 1, 1, 1}; //attributes = flipping, palette

const unsigned char Fireball_X[] = {0, 8, 0, 8}; //relative x coordinates
//we are using 4 sprites, each one has a relative position from the top left sprite

const unsigned char Fireball_Y[] = {0, 0, 8, 8}; //relative y coordinates

const unsigned char Rope_Tile[] = {
	0x0e, 0x0f, 0x1e, 0x1f
};

const unsigned char Rope_Attrib[] = {2, 2, 2, 2}; //attributes = flipping, palette

const unsigned char Rope_X[] = {0, 8, 0, 8}; //relative x coordinates
//we are using 4 sprites, each one has a relative position from the top left sprite

const unsigned char Rope_Y[] = {0, 0, 8, 8}; //relative y coordinates

const unsigned char Friend_X[] = {0, 8, 0, 8}; //relative x coordinates
//we are using 4 sprites, each one has a relative position from the top left sprite

const unsigned char Friend_Y[] = {0, 0, 8, 8}; //relative y coordinates

const unsigned char Friend_Tile[] = {
	0x80, 0x81, 0x90, 0x91, //friend-hanging
};

const unsigned char Friend_Fall_Tile[] = {
	0x82, 0x83, 0x92, 0x93, //friend-falling
};

const unsigned char Friend_Floor_Tile[] = {
	0x84, 0x85, 0x94, 0x95,//friend-on floor
};

enum {Hang, Fall, Floor, Shadow};


const unsigned char MetaSprite_Attrib[] = {0, 0, 0, 0}; //attributes = flipping, palette

const unsigned char MetaSprite_X[] = {0, 8, 0, 8}; //relative x coordinates
//we are using 4 sprites, each one has a relative position from the top left sprite

// Prototypes
void All_Off (void);
void All_On (void);
void Reset_Scroll (void);
void Load_Palette (int pal);
void update_Sprites (void);
void four_Sides (void);
void collide_Check_LR (void);
void collide_Check_UD (void);
void collide_Check_rope (void);
void Load_Good_Text (void);
void Load_Bad_Text (void);
void Load_Intro_Text (void);
void update_title(void);
void move_logic (void);
void sprite_logic (void);
void Draw_Background (void);
void Clear_sprite_data(void);
void Spawn_sprite(int sprx, int spry, int sprtype);
void update_pause(void);
void update_pause2(void);

void __fastcall__ memcpy (void* dest, const void* src, int count);
void Wait_Vblank(void);
void __fastcall__ UnRLE(const unsigned char *data);
void Get_Input(void);

// Audio
void __fastcall__ Play_Fx(unsigned char effect);
void __fastcall__ Reset_Music(void);
void __fastcall__ Play_Music(unsigned char song);
void __fastcall__ Mute_Pulse(void);
void __fastcall__ Unmute_Pulse(void);
void __fastcall__ Music_Update(void);
