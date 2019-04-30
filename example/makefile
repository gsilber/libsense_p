all: 
	make -C simple
	cp simple/simple bin/
	make -C sensors
	cp sensors/sensors bin/
	make -C joystick
	cp joystick/joystick bin/
	make -C gyro
	cp gyro/gyro bin/gyro
	make -C mag
	cp mag/mag bin/mag
	make -C doomsday
	cp doomsday/doomsday bin/doomsday
	make -C binclock
	cp binclock/binclock bin/binclock
	make -C maze
	cp maze/maze bin/maze
	make -C joyshell
	cp joyshell/joyshell bin/joyshell
clean:
	make -C simple clean
	make -C sensors clean
	make -C joystick clean
	make -C gyro clean
	make -C mag clean
	make -C doomsday clean
	make -C binclock clean
	make -C maze clean
	make -C joyshell clean
	rm -f bin/simple bin/sensors bin/joystick bin/gyro bin/mag bin/doomsday bin/binclock bin/maze bin/joyshell
