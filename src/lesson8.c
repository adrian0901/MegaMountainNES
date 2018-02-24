/*	for cc65, for NES
 *  mega mountain NES port by adrian09_01, based on tutorials by nesdoug, Pently added by @PinoBatch
 */
 


#include "DEFINE.c"


// these are the 4 backgrounds
// generated with NES Screen Tool, with RLE option on
#include "BG/title.h" //title screen BG
#include "BG/1.h" // called n1
#include "BG/2.h" // called n2
#include "BG/3.h" // called n3
#include "BG/4.h" // called n4
#include "BG/5.h" // called n4
#include "BG/6.h" // called n4
#include "BG/7.h" // called n4
#include "BG/8.h" // called n4
#include "BG/9.h" // called n4
#include "BG/10.h" // called n4
#include "BG/11.h" // called n4
#include "BG/12.h" // called n4
#include "BG/13.h" // called n4
#include "BG/14.h" // called n4
#include "BG/finale.h" // called n4
#include "BG/intro.h" // called n4


const unsigned char * const All_Backgrounds[]={title,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12,n13,n14,finale,intro};
// pointers to the address of each background

// collision data, made by exporting csv from Tiled, and slight modification
#include "BG/1.csv" // called c1
#include "BG/2.csv" // called c2
#include "BG/3.csv" // called c3
#include "BG/4.csv" // called c4
#include "BG/5.csv" // called c4
#include "BG/6.csv" // called c4
#include "BG/7.csv" // called c4
#include "BG/8.csv" // called c4
#include "BG/9.csv" // called c4
#include "BG/10.csv" // called c4
#include "BG/11.csv" // called c4
#include "BG/12.csv" // called c4
#include "BG/13.csv" // called c4
#include "BG/14.csv" // called c4

const unsigned char * const All_Collision_Maps[] = {c1,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c14,c1};





void main (void) {
	All_Off(); // turn off screen
	++new_background;
	Load_Palette(0);
	Reset_Scroll();
	Reset_Music(); // note, this is famitone init, and I added the music data address. see famitone2.s
	All_On(); // turn on screen
	while (1){ // infinite loop
	Get_Input();	
	if (game_state == 2) {
	if ((joypad1 & START) != 0){
				for (spr_loop = 0; spr_loop < 255; ++spr_loop) {
				SPRITES[spr_loop] = 240;
				}
				for (spr_loop = 1; spr_loop < 16; ++spr_loop) {
				actor_on[spr_loop] = 0;
				actor_type[spr_loop] = 0;
				actor_facing[spr_loop] = 0;
				actor_x[spr_loop] = 0;
				actor_y[spr_loop] = 0;
				actor_extradata[spr_loop] = 0;
				actor_extradata2[spr_loop] = 0;
				actor_extradata3[spr_loop] = 0;
				box_prepared = 0;
				}
				game_mode = 0;
				friend_state = 0;
				Text_Position = 0;
				screen_num = 0;
				which_BGD = 0;
				Load_Palette(0);
				Reset_Music();			
				++new_background;
				final_timer = 0;
				game_state = 0;
				end_timer = 0;
				}
	}
	if (game_state == 0) {
		while (NMI_flag == 0);
		if (new_background > 0) {
			Draw_Background();
			new_background = 0;
		}
		Music_Update();
		update_title();
		
		NMI_flag = 0;
	}
	if (game_state >= 1) {
		while (NMI_flag == 0); // wait till NMI
		if (new_background > 0) {
			screen_num += 1;
			Draw_Background();
			if (game_state == 1) {
			X1 = x_spawns[screen_num];
			Y1 = y_spawns[screen_num];
			}
			exit_dir = exit_table[screen_num];
			sprn=0;
			if (game_state == 1) {
			Clear_sprite_data();
			}
			//screen dependant stuff
			switch(screen_num) {
				case 1:
				Load_Palette(1);
				if (game_state == 2) {
					final_timer = 0;
					Load_Palette(6);
					Spawn_sprite(0x30, 0xC0, 5);
				}
				break;
				case 6:
				Load_Palette(2);
				break;
				case 7:
				Spawn_sprite(0x20, 0x50, 3);
				Spawn_sprite(0x20, 0x60, 3);
				Spawn_sprite(0x20, 0x70, 3);
				Spawn_sprite(0x20, 0x80, 3);
				break;
				case 8:
				Load_Palette(3);
				break;
				case 9:
				Load_Palette(4);
				break;
				case 11:
				Spawn_sprite(0x30, 0x50, 3);
				Spawn_sprite(0x30, 0x60, 3);
				Spawn_sprite(0x30, 0x70, 3);
				break;
				case 14:
				Load_Palette(5);
				Spawn_sprite(0xA0, 0x4F, 4);
				break;
				case 16:
				Load_Palette(6);
				break;
			}
			if (game_mode == 1) {
			switch(screen_num) {
				case 2:
				Spawn_sprite(0x30, 0x90, 1);
				Spawn_sprite(0x50, 0xA0, 1);
				Spawn_sprite(0x80, 0x90, 1);
				Spawn_sprite(0xC0, 0x80, 1);
				Spawn_sprite(0xC0, 0x80, 0);
				Spawn_sprite(0xB0, 0x60, 0);
				break;
				case 3:
				Spawn_sprite(0xA0, 0x60, 2);
				Spawn_sprite(0x60, 0x30, 2);
				Spawn_sprite(0x20, 0x30, 2);
				break;
				case 4:
				Spawn_sprite(0x70, 0x80, 1);
				Spawn_sprite(0x80, 0x90, 1);
				Spawn_sprite(0x90, 0xA0, 1);
				Spawn_sprite(0x40, 0x80, 1);
				Spawn_sprite(0x50, 0x90, 1);
				break;
				case 5:
				Spawn_sprite(0xB0, 0x40, 0);
				Spawn_sprite(0xB0, 0x60, 0);
				Spawn_sprite(0xD0, 0xC0, 2);
				Spawn_sprite(0xF0, 0xA0, 1);
				Spawn_sprite(0xF0, 0xB0, 1);
				break;
				case 6:
				Spawn_sprite(0x60, 0x80, 2);
				Spawn_sprite(0x40, 0xB0, 2);
				Spawn_sprite(0x70, 0xC0, 1);
				Spawn_sprite(0xB0, 0x50, 2);
				break;
				case 7:
				Spawn_sprite(0xC0, 0x40, 2);
				Spawn_sprite(0xD0, 0x20, 2);
				break;
				case 8:
				Spawn_sprite(0x60, 0xB0, 1);
				Spawn_sprite(0x60, 0xC0, 1);
				Spawn_sprite(0x80, 0xC0, 1);
				Spawn_sprite(0x80, 0xD0, 1);
				Spawn_sprite(0x40, 0x50, 0);
				Spawn_sprite(0x40, 0x80, 0);
				Spawn_sprite(0x60, 0x10, 2);
				Spawn_sprite(0x80, 0x10, 2);
				break;
				case 9:
				Spawn_sprite(0x60, 0xA0, 0);
				Spawn_sprite(0x60, 0xB0, 0);
				Spawn_sprite(0x20, 0x60, 0);
				Spawn_sprite(0x50, 0x20, 0);
				break;
				case 10:
				Spawn_sprite(0x60, 0x30, 1);
				Spawn_sprite(0x80, 0x20, 1);
				Spawn_sprite(0x60, 0x90, 1);
				Spawn_sprite(0x80, 0x80, 1);
				Spawn_sprite(0xB0, 0x70, 2);
				Spawn_sprite(0xD0, 0x70, 2);
				break;
				case 11:
				Spawn_sprite(0x50, 0x70, 0);
				Spawn_sprite(0xA0, 0x80, 2);
				break;
				case 12:
				Spawn_sprite(0x80, 0x20, 0);
				Spawn_sprite(0x90, 0x30, 0);
				Spawn_sprite(0xA0, 0x40, 0);
				Spawn_sprite(0xC0, 0x70, 0);
				Spawn_sprite(0xD0, 0x80, 0);
				Spawn_sprite(0xE0, 0x90, 0);
				Spawn_sprite(0xB0, 0xB0, 0);
				Spawn_sprite(0xC0, 0xC0, 0);
				Spawn_sprite(0xD0, 0xD0, 0);
				break;
			}
			}
			level_loaded = 0;
			new_background = 0;
		}
		//every_frame();	// moved this to the nmi code in reset.s for greater stability
		if (paused == 0) {
		move_logic();
		update_pause();
		}
		else {
		update_pause2();
		}
		update_Sprites();
		Music_Update();
		
		NMI_flag = 0;
	}
	}
}
	
// inside the startup code, the NMI routine will ++NMI_flag and ++Frame_Count at each V-blank
	
	
	
	
void All_Off (void) {
	PPU_CTRL = 0;
	PPU_MASK = 0; 
}

	
void All_On (void) {
	PPU_CTRL = 0x90; // screen is on, NMI on
	PPU_MASK = 0x1e; 
}
	
void Reset_Scroll (void) {
	PPU_ADDRESS = 0;
	PPU_ADDRESS = 0;
	SCROLL = 0;
	SCROLL = 0;
}

void Load_Palette (int pal) {
	All_Off();
	PPU_ADDRESS = 0x3f;
	PPU_ADDRESS = 0x00;
	for( index = 0; index < sizeof(RED_PALETTE); ++index ){
	switch(pal) {
	case 0:
		PPU_DATA = TITLE_PALETTE[index];
	break;
	case 1:
		PPU_DATA = DAY_PALETTE[index];
	break;
	case 2:
		PPU_DATA = RED_PALETTE[index];
	break;
	case 3:
		PPU_DATA = SUNSET_PALETTE[index];
	break;
	case 4:
		PPU_DATA = NIGHT_PALETTE[index];
	break;
	case 5:
		PPU_DATA = FINAL_PALETTE[index];
	break;
	case 6:
		PPU_DATA = INTRO_PALETTE[index];
	break;
	}
	}
	All_On();
}

void update_pause (void) {
	++since_last_pause;
	if (since_last_pause > 10) {
		if ( ((joypad1 & START) != 0) && ((joypad1old & START) == 0) ){
			since_last_pause = 0;
			Play_Fx(1);
			joypad1 = 0;
			joypad1old = 0;
			paused = 1;
			Mute_Pulse();
		}
	}
}

void update_pause2 (void) {	
	PPU_MASK = 0xFE; 
	++since_last_pause;
	if (since_last_pause > 10) {
		if ( ((joypad1 & START) != 0) && ((joypad1old & START) == 0) ){
			since_last_pause = 0;
			Play_Fx(1);
			joypad1 = 0;
			joypad1old = 0;
			paused = 0;
			Unmute_Pulse();
		}
	}
}

void Clear_sprite_data(void) {
	for (spr_loop = 0; spr_loop < 255; ++spr_loop) {
		SPRITES[spr_loop] = 240;
	}
	for (spr_loop = 1; spr_loop < 16; ++spr_loop) {
		actor_on[spr_loop] = 0;
		actor_facing[spr_loop] = 0;
	}
}

void Spawn_sprite(int sprx, int spry, int sprtype){
		sprn += 1;
		actor_on[sprn] = 1;
		actor_x[sprn] = sprx;
		actor_y[sprn] = spry;
		actor_type[sprn] = sprtype;
		if (actor_type[sprn] == 2) {
			actor_extradata[sprn] = sprx;
			actor_extradata3[sprn] = spry;
		}
}

void sprite_logic(void) {
	for (spr_loop = 1; spr_loop < 16; ++spr_loop) {
			switch (actor_type[spr_loop]) {
			case 0:
			case 3:
				switch (actor_facing[spr_loop]) {
				case 0:
					corner = ((actor_x[spr_loop]-1 & 0xf0) >> 4) + (actor_y[spr_loop] & 0xf0); // top right
					if (C_MAP[corner] == 1 || C_MAP[corner] == 3) {
					actor_facing[spr_loop] = 1;
					}
					--actor_x[spr_loop];
				break;
				case 1:
					corner = ((actor_x[spr_loop]+12 & 0xf0) >> 4) + (actor_y[spr_loop] & 0xf0); // top right
					if (C_MAP[corner] == 1 || C_MAP[corner] == 3) {
					actor_facing[spr_loop] = 0;
					}
					++actor_x[spr_loop];
				break;
				}
				
					if (actor_on[spr_loop] == 1) {
					switch(actor_type[spr_loop]){
					case 0:
					if (X1-(actor_x[spr_loop]-8) <= 16 & Y1-(actor_y[spr_loop]-8) <= 16) {
					Play_Fx(2);
					Play_Fx(3);
					X1 = x_spawns[screen_num];
					Y1 = y_spawns[screen_num];
					}
					break;
					case 3:
					if (X1-(actor_x[spr_loop]-8) <= 16 & Y1-(actor_y[spr_loop]-8) <= 16) {
					--Y1;
					--Y1;
					climb = 1;
					}	
					break;
					}
					}
			break;
			case 1:
				switch (actor_facing[spr_loop]) {
				case 0:
					corner = ((actor_x[spr_loop] & 0xf0) >> 4) + (actor_y[spr_loop]-1 & 0xf0); // top right
					if (C_MAP[corner] == 1) {
					actor_facing[spr_loop] = 1;
					}
					--actor_y[spr_loop];
				break;
				case 1:
					corner = ((actor_x[spr_loop]+12 & 0xf0) >> 4) + (actor_y[spr_loop]+16 & 0xf0); // top right
					if (C_MAP[corner] == 1) {
					actor_facing[spr_loop] = 0;
					}
					++actor_y[spr_loop];
				break;
				}
				if (X1-(actor_x[spr_loop]-8) <= 16 & Y1-(actor_y[spr_loop]-8) <= 16) {
					if (actor_on[spr_loop] == 1) {
					Play_Fx(2);
					Play_Fx(3);
					X1 = x_spawns[screen_num];
					Y1 = y_spawns[screen_num];
					}
				}
			break;
			case 2:
				++actor_facing[spr_loop];
				if (actor_facing[spr_loop] > 2) {
				++actor_extradata2[spr_loop];
				actor_facing[spr_loop] = 0;
				}
				if (actor_extradata2[spr_loop] > 31) {
					actor_extradata2[spr_loop] = 0;
				}
				actor_x[spr_loop] = actor_extradata[spr_loop]+CIRCLEX[actor_extradata2[spr_loop]]*3;
				actor_y[spr_loop] = actor_extradata3[spr_loop]+CIRCLEY[actor_extradata2[spr_loop]]*3;
				if (X1-(actor_x[spr_loop]-8) <= 16 & Y1-(actor_y[spr_loop]-8) <= 16) {
					if (actor_on[spr_loop] == 1) {
					Play_Fx(2);
					Play_Fx(3);
					X1 = x_spawns[screen_num];
					Y1 = y_spawns[screen_num];
					}
				}
			break;
			case 4:
			switch(friend_state) {
				case 0:
					++actor_facing[spr_loop];
					if (actor_facing[spr_loop] > 10) {
						++actor_extradata[spr_loop];
						if (actor_extradata[spr_loop] > 1) {
							actor_extradata[spr_loop] = -1;
						}
						actor_y[spr_loop] = actor_y[spr_loop] + actor_extradata[spr_loop];
						actor_facing[spr_loop] = 0;
					}
					if (X1-(actor_x[spr_loop]-8) <= 16 & Y1-(actor_y[spr_loop]-8) <= 16) {
					if (actor_on[spr_loop] == 1) {
					Play_Fx(4);
					friend_state = 1;
					game_state = 2;
					Reset_Music();
					}
					}
				break;
				case 1:
					++actor_y[spr_loop];
					--X1;
					--X1;
					corner = ((actor_x[spr_loop]+12 & 0xf0) >> 4) + (actor_y[spr_loop]+16 & 0xf0); // top right
					if (C_MAP[corner] == 1) {
					friend_state = 2;
					}
				break;
				case 2:
					dir = 0;
					++final_timer;
					if (game_mode == 0) {
						PPU_MASK = 0x1F; 
					}
					if (final_timer > 10) {
						if (game_mode == 0) {
						Load_Bad_Text();
						}
						else {
						Load_Good_Text();	
						}
						final_timer = 0;
					}
				break;
			}
			break;
			case 5:
				++actor_facing[spr_loop];
				X1 = 0x10;
				Y1 = 0xC0;
				if (actor_facing[spr_loop] >= 254) {
					if (actor_extradata[spr_loop] == 0) {
					actor_extradata[spr_loop] = 1;
					Play_Music(2);
					Spawn_sprite(0x00, 0xC0, 6);
					}
				}
				if (final_timer > actor_x[spr_loop]) {
					actor_x[spr_loop] = final_timer;
				}
			break;
			case 6:
				++actor_facing[spr_loop];
				if (actor_facing[spr_loop] >= 100) {
					if (actor_extradata[spr_loop] == 0) {
					++actor_x[spr_loop];
					++actor_x[spr_loop];
					++actor_x[spr_loop];
					++actor_x[spr_loop];
					final_timer = actor_x[spr_loop]+8;
					}
				}
				if (actor_x[spr_loop] >= 250) {
					if (actor_extradata2[spr_loop] == 0) {
					final_timer = 0;
					actor_extradata2[spr_loop] = 1;
					}
					actor_extradata[spr_loop] = 1;
					++final_timer;
					if (final_timer > 10) {
						Load_Intro_Text();
						final_timer = 0;
					}
				}
			break;
	}
	}
}

void Load_Good_Text(void) {
	if (box_prepared == 0) {
		if (Text_Position < sizeof(GOOD_END_TEXT)){
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x01 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x21 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x41 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x61 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		++Text_Position;
		Reset_Scroll();
		}
		else {
		Play_Music(1);
		++new_background;
		Text_Position = 0;
		box_prepared = 1;
		}
	}
	if (box_prepared == 1) {
	if (Text_Position < sizeof(GOOD_END_TEXT-1)){
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x21 + Text_Position; //	about the middle of the screen
		PPU_DATA = GOOD_END_TEXT[Text_Position];
		Play_Fx(5);
		++Text_Position;		
		Reset_Scroll();
	}
	}
}

void Load_Bad_Text(void) {
	if (box_prepared == 0) {
		if (Text_Position < sizeof(BAD_END_TEXT)){
		Reset_Scroll(); 
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x01 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x21 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x41 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x61 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		++Text_Position;
		Reset_Scroll();
		
		}
		else {
		Play_Music(2);	
		++new_background;
		Text_Position = 0;
		box_prepared = 1;
		}
	}
	if (box_prepared == 1) {
	if (Text_Position < sizeof(BAD_END_TEXT-1)){
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x21 + Text_Position; //	about the middle of the screen
		PPU_DATA = BAD_END_TEXT[Text_Position];
		Play_Fx(5);
		++Text_Position;	
		Reset_Scroll();
	}
	}
}

void Load_Intro_Text(void) {
	if (box_prepared == 0) {
		if (Text_Position < sizeof(INTRO_TEXT)){
		Reset_Scroll(); 
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x02 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x22 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		Reset_Scroll();
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x42 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x62 + Text_Position; //	about the middle of the screen
		PPU_DATA = 0x5B;
		++Text_Position;
		Reset_Scroll();
		
		}
		else {
		Play_Music(2);	
		which_BGD = 16;
		++new_background;
		X1 = 0x10;
		Y1 = 0xC0;
		Text_Position = 0;
		box_prepared = 1;
		}
	}
	if (box_prepared == 1) {
	if (Text_Position < sizeof(INTRO_TEXT-1)){
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x22 + Text_Position; //	about the middle of the screen
		PPU_DATA = INTRO_TEXT[Text_Position];
		PPU_ADDRESS = 0x21;				//	set an address in the PPU of 0x21ca
		PPU_ADDRESS = 0x42 + Text_Position; //	about the middle of the screen
		PPU_DATA = INTRO2_TEXT[Text_Position];
		Play_Fx(5);
		++Text_Position;	
		Reset_Scroll();
	}
	else {
		++end_timer;
		if (end_timer > 32) {
			for (spr_loop = 0; spr_loop < 255; ++spr_loop) {
			SPRITES[spr_loop] = 240;
			}
			for (spr_loop = 1; spr_loop < 16; ++spr_loop) {
			actor_on[spr_loop] = 0;
			actor_type[spr_loop] = 0;
			actor_facing[spr_loop] = 0;
			actor_x[spr_loop] = 0;
			actor_y[spr_loop] = 0;
			actor_extradata[spr_loop] = 0;
			actor_extradata2[spr_loop] = 0;
			actor_extradata3[spr_loop] = 0;
			box_prepared = 0;
			}
			game_mode = 0;
			friend_state = 0;
			Text_Position = 0;
			screen_num = 0;
			which_BGD = 0;
			Load_Palette(0);
			Reset_Music();			
			++new_background;
			final_timer = 0;
			game_state = 0;
			end_timer = 0;
		}
	}
	}
}

void update_Sprites (void) {
	state4 = state << 2; // shift left 2 = multiply 4
	index4 = 0;
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + Y1; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = 0; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + X1; // relative x + master x
		++index4;
	}
	for (spr_loop = 1; spr_loop < 16; ++spr_loop) {
	if (actor_on[spr_loop] == 1) {
	for (index = 0+(spr_loop-1)*4; index < 1+(spr_loop-1)*4; ++index ){
	for (metaspritedata = 0; metaspritedata < 4; ++metaspritedata) {
		switch (actor_type[spr_loop]) {
		case 0:
		case 1:
		case 2:
		SPRITES[index4+index] = Fireball_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Fireball_Tile[metaspritedata + sprite_state]; // tile numbers
		++index4;
		SPRITES[index4+index] = 1; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Fireball_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		case 3:
		SPRITES[index4+index] = Rope_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Rope_Tile[metaspritedata]; // tile numbers
		++index4;
		SPRITES[index4+index] = 2; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Rope_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		case 4:
		switch (friend_state) {
		case 0:
		SPRITES[index4+index] = Friend_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Friend_Tile[metaspritedata]; // tile numbers
		++index4;
		SPRITES[index4+index] = 1; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Friend_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		case 1:
		SPRITES[index4+index] = Friend_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Friend_Fall_Tile[metaspritedata]; // tile numbers
		++index4;
		SPRITES[index4+index] = 2; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Friend_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		case 2:
		SPRITES[index4+index] = Friend_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Friend_Floor_Tile[metaspritedata]; // tile numbers
		++index4;
		SPRITES[index4+index] = 2; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Friend_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		}
		break;
		case 5:
		SPRITES[index4+index] = Friend_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Friend_Fall_Tile[metaspritedata]; // tile numbers
		++index4;
		SPRITES[index4+index] = 2; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Friend_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		case 6:
		SPRITES[index4+index] = Friend_Y[metaspritedata] + actor_y[spr_loop]; // relative y + master y
		++index4;
		SPRITES[index4+index] = Friend_Fall_Tile[metaspritedata]; // tile numbers
		++index4;
		SPRITES[index4+index] = 3; // attributes, all zero here
		++index4;
		SPRITES[index4+index] = Friend_X[metaspritedata] + actor_x[spr_loop]; // relative x + master x
		++index4;
		break;
		}
	}
	}
	}
	}
}

void four_Sides (void){
	if (X1 < (255-3)){	// find the left side, the first 3 pixels are blank
		X1_Left_Side = X1 + 4;
	}
	else {
		X1_Left_Side = 255;
	}
	if (X1 < (255-12)){	// find the right side, the last 3 pixels are blank
		X1_Right_Side = X1 + 11;
	}
	else {
		X1_Right_Side = 255;
	}
	Y1_Top = Y1+9;	// our top is the same as the master Y
	
	if (Y1 < (255-15)){ // find the bottom side
		Y1_Bottom = Y1 + 15;
	}
	else {
		Y1_Bottom = 255;
	}
}
	
void collide_Check_LR (void){
	four_Sides();	// set the L R bottom top variables
	
		corner = ((X1_Right_Side & 0xf0) >> 4) + (Y1_Top & 0xf0); // top right
		if (C_MAP[corner] == 1) {
			X1 = (X1 & 0xf0) + 4; // if collision, realign
			--Y1;
			climb = 1;
		}

		corner = ((X1_Right_Side & 0xf0) >> 4) + (Y1_Bottom & 0xf0); // bottom right
		if (C_MAP[corner] == 1) {
			X1 = (X1 & 0xf0) + 4; // if collision, realign
			--Y1;
		climb = 1;
		}
		corner = ((X1_Left_Side & 0xf0) >> 4) + (Y1_Top & 0xf0); // top left
		if (C_MAP[corner] == 1) {
			X1 = (X1 & 0xf0) + 12; // if collision, realign
			--Y1;
		climb = 1;
		}

		corner = ((X1_Left_Side & 0xf0) >> 4) + (Y1_Bottom & 0xf0); // bottom left
		if (C_MAP[corner] == 1) {
			X1 = (X1 & 0xf0) + 12; // if collision, realign
			--Y1;
		climb = 1;
		}
}

void collide_Check_rope(void) {
	corner = ((X1+8 & 0xf0) >> 4) + (Y1+8 & 0xf0); // bottom right
	if (C_MAP[corner] == 2) {
			--Y1; // if collision, realign
			--Y1;
			climb = 1;
	}
}

void collide_Check_UD (void){
	four_Sides();
		corner = ((X1_Right_Side & 0xf0) >> 4) + (Y1_Bottom & 0xf0); // bottom right
		if (C_MAP[corner] == 1) {
			Y1 = (Y1 & 0xf0) ; // if collision, realign
		}

		corner = ((X1_Left_Side & 0xf0) >> 4) + (Y1_Bottom & 0xf0); // bottom left
		if (C_MAP[corner] == 1) {
			Y1 = (Y1 & 0xf0); // if collision, realign
		}

		corner = ((X1_Right_Side & 0xf0) >> 4) + (Y1_Top & 0xf0); // top right
		if (C_MAP[corner] == 1)
			Y1 = (Y1 & 0xf0) + 7; // if collision, realign

		corner = ((X1_Left_Side & 0xf0) >> 4) + (Y1_Top & 0xf0); // top left
		if (C_MAP[corner] == 1)
			Y1 = (Y1 & 0xf0) + 7; // if collision, realign
}


void update_title(void) {
	++final_timer;
	for (spr_loop = 0; spr_loop < 255; ++spr_loop) {
		SPRITES[spr_loop] = 240;
	}
	if (final_timer > 254) {
		game_state = 2;
		which_BGD = 1;
		++new_background;
		Play_Music(1);
	}
	if ((joypad1 & A_BUTTON) != 0){
		game_mode = 0;
		game_state = 1;
		Reset_Music();
		Play_Music(0); // song = 0
		++new_background;
	}
	if ((joypad1 & B_BUTTON) != 0){
		game_mode = 1;
		game_state = 1;
		Reset_Music();
		Play_Music(0); // song = 0
		++new_background;
	}
}

void move_logic (void) {
	climb = 0;
	frame++;
	if (X1 < 1) {
		if (exit_table[screen_num] == 0) {
		if (level_loaded == 0) {
			level_loaded = 1;
			++new_background;
		}
		}
	X1 = 1;
	}
	if (X1 > 240) {
		if (exit_table[screen_num] == 1) {
		if (level_loaded == 0) {
			level_loaded = 1;
			++new_background;
		}
		}
	X1 = 240;
	}
	if (Y1 < 2) {
		if (exit_table[screen_num] == 2) {
		if (level_loaded == 0) {
			level_loaded = 1;
			++new_background;
		}
		}
	Y1 = 2;
	}
	if (Y1 > 240) {
		if (exit_table[screen_num] == 3) {
		if (level_loaded == 0) {
			level_loaded = 1;
			++new_background;
		}
		}
		else {
		Play_Fx(2);
		Play_Fx(3);
	X1 = x_spawns[screen_num];
	Y1 = y_spawns[screen_num];
		}
	}
	if (frame < 15) {
		sprite_state = 0;
	}
	if (frame >= 15 && frame < 30) {
		sprite_state = 4;
	}
	if (frame > 45) {
		sprite_state = 4;
	}
	if (frame >= 30 && frame < 45) {
		sprite_state = 0;
	}
	if (frame < 30) {
		if (dir == 0) {
		state = Going_Right;
		}
		if (dir == 1) {
		state = Going_Left;
		}
	}
	if (frame >= 30) {
		if (dir == 0) {
		state = Going_Down;
		}
		if (dir == 1) {
		state = Going_Up;
		}
	}
	if (frame >= 60) {
		frame = 0;
	}
	if (game_state < 2) {
	if ((joypad1 & RIGHT) != 0){
		++X1;
		dir = 0;
	}
	if ((joypad1 & LEFT) != 0){
		--X1;
		dir = 1;
	}	
	}
	collide_Check_LR();
	
	if (climb == 0) {
		++Y1;
	}
	
	collide_Check_rope();
	sprite_logic();
	collide_Check_UD();
}

void Draw_Background (void) {
	All_Off();
	PPU_ADDRESS = 0x20;
	PPU_ADDRESS = 0x00;
	UnRLE(All_Backgrounds[which_BGD]);	// uncompresses our BG tiles

	// now load the collision map to RAM
	p_C_MAP = All_Collision_Maps[which_BGD];
	for (index = 0;index < 240; ++index){
		C_MAP[index] = p_C_MAP[index];
	}
	// 42688 cycles = 9 times slower
	
	Wait_Vblank();	// don't turn on screen until in v-blank
	All_On();
	Reset_Scroll();
	++which_BGD;
	if (which_BGD == 18) // shuffles between 0-3
		which_BGD = 0;
}
