#include <snes.h>
#include <res.h>

#include <vcfe_scroller.h>

#include <scenes.h>

#include "src/code_e.c"

extern Scene* timeline[];
Scene* this_scene;

static unsigned long time = 0;
static unsigned long scene_time = 0;

static key_state key;
static int key_changed = 0;
static unsigned short key_state_last = 0;

static StateMachine snes_state = {
		SCENE_STATE_INIT,
		0,
		0,
};

static char current_scene = 0;
unsigned int frame_start = 1;

static char next_frame = 0;

#define SCENE_COUNT 2

enum SCENE_STATE state = SCENE_STATE_NOP;
enum SCENE_STATE next_state = SCENE_STATE_NOP;

StateMachine state_machine = {
		1,
		2,
		3,
};

/*
 * NMI gets called on every V-Blank
 * - set up dma, hdma
 * - trigger new scenes
 */

static int fu = 0;

static int step = 0;
unsigned int frame_count = 0;

void nmi(void)
{
	int ret;
	int i = 0;

	time++;
	scene_time++;



	/******************************
	 * Handle state changes
	 ******************************/

	if(state != next_state) {
	//	printsnes("state change\n");
		state = next_state;

		if(state == SCENE_STATE_START_SCREEN) {
			this_scene = timeline[0];
			state = SCENE_STATE_INIT;
			if(this_scene->funcs->init_hook) {
				INIDISP = INIDISP | 0x80;
				NMITIMEN = 0x01; // nmi disable

				next_state = this_scene->funcs->init_hook(state, 0);

				INIDISP = INIDISP & ~0x80;
				NMITIMEN = 0x81; // nmi enable
			}

		} else if(state == SCENE_STATE_EXHIBIT_MODE) {
			this_scene = timeline[1];
			state = SCENE_STATE_INIT;
			if(this_scene->funcs->init_hook) {
				INIDISP = INIDISP | 0x80;
				NMITIMEN = 0x01; // nmi disable


				//printsnes("calling init hook\n");
				next_state = this_scene->funcs->init_hook(state, 0);
				//printsnes("init hook done\n");

				INIDISP = INIDISP & ~0x80;
				NMITIMEN = 0x81; // nmi enable
			}
		} else if(state == SCENE_STATE_INIT) {
			INIDISP = INIDISP | 0x80;
			NMITIMEN = 0x01; // nmi disable

			//printsnes("calling init hook\n");
			next_state = this_scene->funcs->nmi_hook(state, 0);
			//printsnes("init hook done\n");

			INIDISP = INIDISP & ~0x80;
			NMITIMEN = 0x81; // nmi enable
		} else {
			next_state = this_scene->funcs->nmi_hook(state, this_scene->params);
		}
	} else {
		//printsnes("nmi\n");
		//snes_print_int(state);
		if(this_scene->funcs->nmi_hook) {
			next_state = this_scene->funcs->nmi_hook(state, this_scene->params);
		}
		//snes_print_int(next_state);
		//printsnes("\n");
	}

	frame_start = 1;
	next_frame = 1;

	frame_count++;
}

/*
 * IRQ is called on soft irq's eg. timers, controllers or
 * when a h-scan value is reached
 */
void irq(void)
{
	//printsnes("irq call\n");

	if(this_scene->funcs->irq_hook) {
		this_scene->funcs->irq_hook(state, this_scene->params);
	}
}

/*
 * INIT
 * called once on startup while forced v-blank is active
 * do whatever you like and take your time.
 */
void init(void)
{
	//printsnes("init call\n");

	state = SCENE_STATE_INIT;

	vcfe_scroller_init();

	this_scene = timeline[1];

	INIDISP = INIDISP | 0x80;
	NMITIMEN = 0x01; // nmi disable



	if(this_scene->funcs->init_hook) {
		next_state = this_scene->funcs->init_hook(state, this_scene->params);
	}

	INIDISP = INIDISP & ~0x80;
	NMITIMEN = 0x81;
}

/*
 * START
 * called once after INIT is done. Endless loop that runs in the background
 * while every frame is drawn.
 */
void start(void)
{
	//int i;
	short key_state_tmp; // = STDCNTRL1;

	do {
		if(next_frame) {
			while(HVBJOY & 0x01);

			key_state_tmp = STDCNTRL1;

			/******************************
			 * Handle key events.
			 ******************************/
			//key_state_tmp = ((short)key_state_tmph << 8) | key_state_tmpl;

			key.dir = (key_state_last ^ key_state_tmp) & key_state_tmp;
			key.val = (key_state_last ^ key_state_tmp);
			key.val |= (key_state_tmp & 0x0C00); // have the up down working all the time

			if(next_state == SCENE_STATE_RUNNING && key.val) {
				//printsnes("calling key hook\n");
				this_scene->funcs->handle_key_hook(state, (void*)&key);
			}

			key_state_last = key_state_tmp;


			if(this_scene->funcs->run_hook) {
				this_scene->funcs->run_hook(state, this_scene->params);
			}


			next_frame = 0;
		}
	} while(1);
}


