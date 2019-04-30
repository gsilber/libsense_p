#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "sense.h"
	
char running=1;
char path[PATH_MAX];

const char* menu[4]={"maze","joystick","binclock","doomsday"};
void ignore_handler(int sig){
}
void handler(int sig){
	running=0;
}

char* getPathFromExecutable(const char* executable,char* newPath){
	int l=strlen(executable);
	int i;
	strcpy(newPath,executable);
	for (i=l-1;i>=0;i--){
		if (newPath[i]=='/'){
			newPath[i]=0;
			break;
		}
	}
}
void launchProgram(const char* executable){
	int pid;
	int status;
	if (pid=fork()){
		waitpid(pid,&status,0);
	} else {
		printf("Launching %s\n",executable);
		execlp(executable,executable,0);
		printf("Failed to launch %x\n",errno);
		exit(1);
	}

}
void callbackFn(unsigned int code){
	char exepath[PATH_MAX];
	strcpy(exepath,path);
	strcat(exepath,"/");
	switch(code){
		case KEY_UP:
			strcat(exepath,menu[0]);
			break;
		case KEY_DOWN:
			strcat(exepath,menu[1]);
			break;
		case KEY_RIGHT:
			strcat(exepath,menu[2]);
			break;
		case KEY_LEFT:
			strcat(exepath,menu[3]);
			break;
		default:
			return;
	}
	launchProgram(exepath);
}

int main(int argc,char* argv[]){
	char exe[PATH_MAX];
	realpath(argv[0],exe);
	getPathFromExecutable(exe,path);
	printf("%s\n",path);
	pi_joystick_t* joystick=getJoystickDevice();
	//ignore sigint so child processes can exit
	signal(SIGINT,ignore_handler);
	signal(SIGHUP,handler);
	signal(SIGTERM,handler);
	while (running){
		pollJoystick(joystick,callbackFn,1000);
	}
	freeJoystick(joystick);
}
