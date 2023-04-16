#include <Arduino.h>
#include <string.h>
#include <SoftwareSerial.h>

#define in1 9 // #define <ten bien> <gia tri chan tren mach arduino>
#define in2 10
#define in3 11
#define in4 6

#define delta 0.8

SoftwareSerial myBluetooth(2,3); // 2 : TX , 3 RX

class Car
{
	private:
		float speed = 255;
		char value;
	public:
		void isConnect(){
			if(myBluetooth.available() > 0){
				Serial.println("Successfully connected!");
				digitalWrite(13 , HIGH);
			}
			else{
				Serial.println("Successfully connected!");
				digitalWrite(13 , LOW);				
			}
		}
		void first_motor_Forward(float speed){
			speed = constrain(speed , 0 , 255);
			analogWrite(in1 , speed);
			digitalWrite(in2 , LOW);
		}
		void second_motor_Forward(float speed){
			speed = constrain(speed , 0 , 255);
			analogWrite(in3 , speed);
			digitalWrite(in4 , LOW);
		}
		void first_motor_Back(float speed){
			speed = constrain(speed , 0 , 255);
			digitalWrite(in1 , LOW);
			analogWrite(in2 , speed);
		}
		void second_motor_Back(float speed){
			speed = constrain(speed , 0 , 255);
			digitalWrite(in3 , LOW);
			analogWrite(in4 , speed);
		}
		void first_motor_Stop(){
			digitalWrite(in1 , LOW);
			digitalWrite(in2 , LOW);
		}
		void second_motor_Stop(){
			digitalWrite(in3 , LOW);
			digitalWrite(in4 , LOW);
		}
		void Forward(float speed)
		{
			first_motor_Forward(speed);
			second_motor_Forward(speed);
		}
		void Back(float speed)
		{
			first_motor_Back(speed);
			second_motor_Back(speed);
		}
		void Stop()
		{
			first_motor_Stop();
			second_motor_Stop();
		}
		void Left(float speed)
		{
			first_motor_Forward(speed);
			second_motor_Back(speed);
		}
		void Right(float speed)
		{
			first_motor_Back(speed);
			second_motor_Forward(speed);
		}
		void basically_control()
		{
			value =myBluetooth.read();

			switch (value)
			{
			case '0':
				speed = 0;
				break;
			case '1':
				speed = 0.1*255;
				break;
			case '2':
				speed = 0.2*255;
				break;
			case '3':
				speed = 0.3*255;
				break;
			case '4':
				speed = 0.4*255;
				break;
			case '5':
				speed = 0.5*255;
				break;
			case '6':
				speed = 0.6*255;
				break;
			case '7':
				speed = 0.7*255;
				break;
			case '8':
				speed = 0.8*255;
				break;
			case '9':
				speed = 0.9*255;
				break;
			case 'q':
				speed = 255;
				break;
			case 'S':
				Stop();
				break;
			case 'B':
				Back(speed);
				break;
			case 'F':
				Forward(speed);
				break;
			case 'R':
				Right(speed);
				break;
			case 'L':
				Left(speed);
				break;
			case 'G':
				first_motor_Forward(speed) , second_motor_Back(delta*speed);
				break;
			case 'I':
				second_motor_Forward(speed) , first_motor_Back(delta*speed);
				break;
			case 'J':
				first_motor_Back(speed) , second_motor_Forward(delta*speed);
				break;
			case 'H':
				second_motor_Back(speed) , first_motor_Forward(delta*speed);
				break;
			}
		}
}TamPhu;


void setup()
{
	Serial.begin(9600);
	myBluetooth.begin(9600);

	pinMode(13 , OUTPUT);
	pinMode(in1 , OUTPUT);
	pinMode(in2 , OUTPUT);
	pinMode(in3 , OUTPUT);
	pinMode(in4 , OUTPUT);

	TamPhu.isConnect();
	TamPhu.Stop();

}

void loop()
{
	TamPhu.basically_control();
}
