#ifndef SNES_CONSTS_H_
#define SNES_CONSTS_H_

enum DMA_MODES {
	DMA_MODE_BYTE,
	DMA_MODE_SHORT,
	DMA_MODE_BYTE_TWICE,
	DMA_MODE_SHORT_TWICE,
	DMA_MODE_INT,
	DMA_MODE_INT_TWICE_SHORT,
};

enum SYNC_MODE_FLAGS {
	SYNC_MODE_PATTERN 	= 1,
	SYNC_MODE_SEQUENCE 	= 2,
	SYNC_MODE_TRACK 	= 4,
	SYNC_MODE_VOICE 	= 8
};

enum SYNC_TIME_MODES {
	SYNC_TIME_MIN,
	SYNC_TIME_MAX,
	SYNC_TIME_COUNT
};

enum SCENE_TYPE {
	SCENE_TYPE_MODE1,
	SCENE_TYPE_MODE2,
	SCENE_TYPE_MODE3,
	SCENE_TYPE_MODE4,
	SCENE_TYPE_MODE5,
	SCENE_TYPE_MODE6,
};

enum SCENE_STATE {
	SCENE_STATE_NOP,
	SCENE_STATE_INIT,

	SCENE_STATE_FADE_IN,
	SCENE_STATE_RUNNING,
	SCENE_STATE_FADE_OUT,

	SCENE_STATE_DEMO_MODE,
	SCENE_STATE_START_SCREEN,
	SCENE_STATE_EXHIBIT_MODE
};

enum EFFECT_FUNC_TIMING {
	EFFECT_FUNC_PRE,
	EFFECT_FUNC_POST,
};


typedef int (*initScenePtr)(char);

struct sync_desc {
	enum SYNC_MODES mode;
	enum SYNC_TIME_MODES time;
	unsigned int value;
};

#define MAX_SCENE_NAME_LENGHT 255

struct scene_desc {
	char name[MAX_SCENE_NAME_LENGHT];
	enum SCENE_TYPE type;
};

typedef int (*func)(enum SCENE_STATE state, void* param);
typedef struct Functions {
	func init_hook;
	func nmi_hook;
	func run_hook;
	func irq_hook;
	func sync_hook;
	func handle_key_hook;
	func deinit_hook;
} Functions;

typedef struct Scene {
	Functions* funcs;
	void* params;
	int in_time;
	int run_time;
	int out_time;
	enum SCENE_STATE* state;
} Scene;

typedef struct key_state {
	unsigned short val;
	unsigned short dir;
} key_state;

/*
#define DEFINE_SCENE_FUNCS(				\
		init_func, 							\
		nmi_func, 							\
		run_func, 							\
		irq_func, 							\
		sync_func) 							\
		static Scene_Main_Funcs funcs = { 	\
			init:	&init_func, 			\
			nmi:	&nmi_func, 				\
			run:	&run_func, 				\
			irq:	&irq_func, 				\
			sync:	&sync_func, 			\
		};
*/

typedef struct StateMachine {
	enum SCENE_STATE scene_state;
	int current_scene;
	char status;
} StateMachine;

extern StateMachine snes_state;

typedef struct ObjData {
	char vpos;
	char hpos;
	short config;
} ObjData;


#endif /* SNES_CONSTS_H_ */
