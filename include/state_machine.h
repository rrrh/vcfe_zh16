// we need a static state machine to hold all the stuff that's relevant..

typedef struct StateMachine {
	char current_scene;
	char status;
	char c;
} StateMachine;
