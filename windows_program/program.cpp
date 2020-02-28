
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include <windows.h>

#include "serial_com.h"
#include "timer.h"

// keyboard input macro
// check if key c is currently pressed
// note that multiple keys can be pressed at once
#define KEY(c) ( GetAsyncKeyState((int)(c)) & (SHORT)0x8000 )

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE h1;
	int max = 180;
	int min = 0;
	const int NMAX = 64;
	char buffer[NMAX];
	int i, n, k, speed;
	short int *v, th1 = 90;
	// note: ints are 2 bytes on the Arduino versus 4 bytes on PC/Windows.
	// we can use short ints in Windows for two byte ints.

	// note this v is exactly analogous to the v in the arduino program
	v = (short int *)buffer;

	speed = 1;
	open_serial("COM5", h1, speed);

	while (1) {

		if (KEY(VK_UP)) {
			th1 += 7;
			if (th1 >= max) th1 = max;
		}
		if (KEY(VK_DOWN)) {

			th1 -= 7;
			if (th1 <= min) th1 = min;
		}
		if (!KEY(VK_DOWN) && (!KEY(VK_UP))){
			if (th1 < 90){
				th1 += 7;
			}
			if (th1 > 90){
				th1 -= 7;
			}

		}
		

		cout << "\n" << th1;
		// send new data every 100 ms
		Sleep(10);

		v[0] = th1;

		n = 2; // number of bytes to send
		serial_send(buffer, n, h1);

		// should wait briefly to complete the send and/or
		// to receive data from Arduino
		Sleep(10);

		// print out what the Arduino sends back
		// this is like a mini serial monitor program
		while (serial_available(h1) > 0) {
			serial_recv(buffer, 1, h1);
			cout << buffer[0];
		}

	}

	close_serial(h1);

	return 0;
}

