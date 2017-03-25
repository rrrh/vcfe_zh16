/*
 * exhibits.h
 *
 *  Created on: 12 Oct 2016
 *      Author: hns
 */

#ifndef INCLUDE_EXHIBITS_H_
#define INCLUDE_EXHIBITS_H_

typedef struct screen_data {
	short* pic;
	short* clr;
	short* map;
} screen_data;

typedef struct sprite_data {
	short* pic;
	short* clr;
};

typedef struct exhibit {
	char label[16];

	screen_data main_screen;
} exhibit;

#endif /* INCLUDE_EXHIBITS_H_ */
