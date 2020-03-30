
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "serial_com.h"
#include "shared_memory.h"

using namespace std;

#define KEY(c) (GetAsyncKeyState((int)(c)) & (SHORT)0x8000)

int main(int argc, char* argv[])	
{
	//declarations and initialisations
	
	int i, speed = 1; // speed of baud rate
	int n = 1000; // size of shared memory block (bytes)
	char name[] = "smem_joystick"; // name of shared memory block
	char *p, *p_ar; // pointer to shared memory and buffer of arduino

	//for serial communication
	HANDLE h1;
	const int NMAX = 64;
	char buffer_in[NMAX], buffer_op[NMAX]; // buffer to send: buffer_in, buffer to recieve buffer_op
	char COM_port[10] = "COM6";
	Sleep(100);

	//opening serial for communication
	open_serial(COM_port, h1, speed);
	cout << "\n press C to continue or X to terminate program";
	while (!KEY('C')) Sleep(1);

	short int *q, *q_ar, *op; // pointer to an array of integers for shared and buffer
	// to be stored in the shared memory block



	// create/access shared memory
	p = shared_memory(name,n);
	p_ar = buffer_in;
	q_ar = (short int*)p_ar;
	// convert the character pointer to an int pointer
	q = (short int *)p;
	i = 1;
	while(1) {
		q_ar[0] = q[0];
		//q_ar[1] = q[1];

		serial_send(buffer_in, 2, h1);
		cout << "\narduino values: " << q_ar[0] << "\t" << q_ar[1];
		if (KEY('X')) break;
		
		// suspend program B for 10ms allowing other
		// programs to operate
		Sleep(10);
		
		//cout << "recieving from arduino\n";
		//serial_recv(buffer_op, 2, h1);	
		//op = (short int* )buffer_op;
		
		//cout << "\ni" <<i;
		//i++;
		//cout << "\noutput from arduino:" << op[0];
		
	}

	
	close_serial(h1);

	Sleep(1000);

	cout << "\ndone.\n";
	_getch();

	return 0;
}

