#include <Arduino.h>
#include <Servo.h>


Servo serv;
void setup(){
	
	Serial.begin(115200);
	pinMode(13,OUTPUT);
	serv.attach(8);
}

void loop(){
	
	const int NMAX = 64;
	char buffer_ar[NMAX];
	static int i = 0;
	int	len,n;
	int *q;
	char * p;
	int pos;

	//check if bytes are available at port
	while(Serial.available() == 0) {
		i++;
	}
	len = 2;
	
	// readbytes reads the buffer till length specified and returns the number
	// of bytes read
	n = Serial.readBytes(buffer_ar,len);
	if(n < len){
		Serial.print("\nerror, not enough data read");
	}
	
	// using memory buffer/chunks
	p = buffer_ar;
	q = (int* )p;
	pos = q[0];
	
	serv.writeMicroseconds(pos);
	
	
	//Serial.write(buffer_ar,2);
	delay(10);

}