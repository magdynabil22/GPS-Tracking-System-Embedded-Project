#include "GPIO.h"
#include "UART.h"
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define EARTHRADIUS 6371000.0 // Earth's radius in meters
const double PI=3.14159265358979323846;


 void GPSscan(char * lat, char * longt) //Get the message from gps then extract latitude and longitude
	 {
char d;
int i=0,j=0,result=1;

do
{
	d=UART5_GPS_read();  //d="$GPRMC"
}while(d!=',');


 do
{
 d = UART5_GPS_read(); //numbers that represent time
} while (d != ',');
 
d = UART5_GPS_read(); //'A'
if(d=='A'){
 d = UART5_GPS_read(); //','
 d = UART5_GPS_read(); // 'First latitude number (3)'
while (d != ',') // loop to take the latitude
	{
    lat[i++] = d; //latitude array
  d = UART5_GPS_read();
 }
   lat[i] = '\0';

   d = UART5_GPS_read(); //'N'
		if(d=='N'){
			d = UART5_GPS_read();  //','
			d = UART5_GPS_read(); // 'First longitude number (0)'
 while (d != ',') {
longt[j++] = d; // loop to take the longitude
  d = UART5_GPS_read();
  }
 longt[j] = '\0';
result = 0; 
}
}
}


double toRad(double angle) {
    return (angle * PI / 180);
}

double getDistance(double startLong, double startLat, double endLong, double endLat) {
    double lambda_A = toRad(startLong);
    double phi_A = toRad(startLat);
    double lambda_B = toRad(endLong);
    double phi_B = toRad(endLat);
    double delta_lambda = lambda_B - lambda_A;
    double delta_phi = phi_B - phi_A;
    double a = pow(sin(delta_phi / 2), 2) + cos(phi_A) * cos(phi_B) * pow(sin(delta_lambda / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTHRADIUS * c;
}


float toDECIMALDEGREE(float coordinate) //change the degree minutes received from gps to decimal degree
	{
    int degrees = (int)(coordinate / 100);
    float minutes = coordinate - degrees * 100;
    float decimalDegrees = degrees + minutes / 60.0;

    return decimalDegrees;
}


int main(void){

	char i,latitude[20],longitude[20];
	double displacement,lat1,lon1,lat2,lon2;
	double lonFINAL= 31.627247;//the end destination long..
	double latFINAL=30.149965;// the end destination lat...
        initPortF();
	initPortD();
	UART5_GPS_init();
	UART0_GPS_init();
	
	
	while(1){

		GPSscan(latitude,longitude);
		lat1 =atof(latitude);
		lon1 = atof(longitude);
		lat2 = toDECIMALDEGREE(lat1);
		lon2 = toDECIMALDEGREE(lon1);
		displacement=getDistance(lon2,lat2,lonFINAL,latFINAL);
		if(displacement>20)
			turn_led(RED);
		else if(displacement<20 &&displacement>10)
			turn_led(YELLOW);
		else 
			turn_led(GREEN);
	  	
}
}
