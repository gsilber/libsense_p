#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "sense.h"

#define SENSITIVITY 20

int run = 1;
int win = 0;

typedef struct
{
	int ballx;
	int bally;
	int ballxprev;
	int ballyprev;
} gamestate_t;

void handler(int sig)
{
	printf("\nExiting...\n");
	run = 0;
}

uint16_t maze[8][8] = {
	{0, 0, 0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
	{0xFFFF, 0xFFFF, 0, 0xFFFF, 0xFFFF, 0, 0, 0xFFFF},
	{0xFFFF, 0xFFFF, 0, 0, 0, 0, 0xFFFF, 0xFFFF},
	{0xFFFF, 0xFFFF, 0xFFFF, 0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
	{0xFFFF, 0, 0, 0, 0, 0, 0, 0xFFFF},
	{0xFFFF, 0, 0xFFFF, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF},
	{0xFFFF, 0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
	{0xFFFF, 0, 0, 0, 0, 0, 0, 0}};

void initGame(gamestate_t *game)
{
	game->ballx = game->bally = game->ballxprev = game->ballyprev = 0;
}
void drawMaze(sense_fb_bitmap_t *screen, uint16_t color)
{
	int i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			setPixel(screen, i, j, color & maze[j][i]);
		}
	setPixel(screen, 7, 7, getColor(0, 255, 0));
}

void drawBall(sense_fb_bitmap_t *screen, gamestate_t *state, uint16_t color)
{
	setPixel(screen, state->ballxprev, state->ballyprev, 0);
	setPixel(screen, state->ballx, state->bally, color);
	printf("%d %d\n",state->ballx, state->bally);
}


void moveBall(gamestate_t *state, coordinate_t *gyroData)
{
	int x = state->ballx;
	int y = state->bally;
	state->ballxprev = state->ballx;
	state->ballyprev = state->bally;
	if (gyroData->x  > SENSITIVITY)
		y -= 1;
	if (gyroData->x  < -1 * SENSITIVITY)
		y += 1;
	if (gyroData->y  > SENSITIVITY)
		x -= 1;
	else if (gyroData->y < -1 * SENSITIVITY)
		x += 1;


	if (x!=state->ballx && x >= 0 && x < 8 && maze[state->bally][x] == 0)
		state->ballx = x;
	if (y!=state->bally && y >= 0 && y < 8 && maze[y][state->ballx] == 0)
		state->bally = y;
	if (state->ballx == 7 && state->bally == 7)
	{
		run = 0;
		win = 1;
	}
}

/*animationStep
  screen: a bitmap to draw on
  step: the animation step (0-3)
  color: the color of the animation
  draws a box of width step+1 clearing the middle*/
void animationStep(sense_fb_bitmap_t *screen, int step, int color)
{
	int i, j;
	for (i = 3 - step; i < 5 + step; i++)
		for (j = 3 - step; j < 5 + step; j++)
			if (i == 3 - step || i == 4 + step || j == 3 - step || j == 4 + step)
				setPixel(screen, i, j, color);
			else
				setPixel(screen, i, j, 0);
}
/*explodeAnimation
    fb: a framebuffer object
    color: the color of the animation
    executes an explode animation*/
void explodeAnimation(pi_framebuffer_t *fb, uint16_t color)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		animationStep(fb->bitmap, i, color);
		usleep(100000);
	}
}

int main(int argc,char* argv[])
{
	int cnt = 0, i,starting=1;
	pi_i2c_t *device;
	coordinate_t data;
	gamestate_t game;
	initGame(&game);
	signal(SIGINT, handler);
	printf("Set the pi flat on the ground for calibration\n");
	pi_framebuffer_t *fb = getFBDevice();
	if (!fb)
		return 0;
	clearBitmap(fb->bitmap, 0);
	drawMaze(fb->bitmap, getColor(0, 0, 255));
	drawBall(fb->bitmap, &game, getColor(255, 0, 0));
	device = geti2cDevice();
	if (device)
	{
		configureAccelGyro(device);
		while (run)
		{
			usleep(2000);
			while (run && getGyroPosition(device, &data)){
				if (data.x!=0.0 && starting){
					starting=0;
					printf("You may pick up the pi and begin playing\n");
				}
				if (!(cnt % 10))
				{
					moveBall(&game, &data);
					drawBall(fb->bitmap, &game, getColor(255, 0, 0));
				}
				cnt++;
			}
		}
		if (win)
		{
			for (i = 0; i < 5; i++)
			{
				explodeAnimation(fb, getColor(255, 0, 0));
				explodeAnimation(fb, getColor(0, 0, 255));
			}
		}
		freei2cDevice(device);
	}
	clearBitmap(fb->bitmap, 0);
	freeFrameBuffer(fb);
	return 0;
}
