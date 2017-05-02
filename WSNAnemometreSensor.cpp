#include "WSNAnemometreSensor.h"

Anemometre::Anemometre()
{
	_sensorPin = SensorPin;
	_offset = Offset;
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	anemometreValue = 0;
	tableauAnemometre[_tailleEchantillon];
	indexAnemometre=0; 
	nbTour=0;
};

Anemometre::Anemometre(uint8_t pin)
{
	_sensorPin = pin;
	_offset = Offset;
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	anemometreValue = 0;
	tableauAnemometre[_tailleEchantillon];
	indexAnemometre=0; 
	nbTour=0;
};
void Anemometre::init()
{
	pinMode(_sensorPin, INPUT);
	_sensorPin = SensorPin;
	_offset = Offset;
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	anemometreValue = 0;
	tableauAnemometre[_tailleEchantillon];
	indexAnemometre=0; 
	nbTour=0;
	_etatPin=0;

};
void Anemometre::init(uint8_t offset, uint8_t mesure, uint32_t Convertion,uint8_t taille)
{
	_offset = offset;
	_intervalMesure = mesure;
	_intervalConvertion = Convertion;
	_tailleEchantillon = taille;
	tableauAnemometre[_tailleEchantillon];
	indexAnemometre=0; 
	nbTour=0;
};

uint8_t Anemometre::getMesure()
{
	uint8_t tmp = anemometreValue;
	anemometreValue = 0;
	return tmp*2*3.14*7.2*0.01;
};

uint16_t Anemometre::moyenne(uint8_t* arr, uint8_t number)
{
	uint8_t i;
	 int max,min;
	 uint16_t avg;
	 uint16_t amount=0;

	 if(number<5){  //less than 5, calculated directly statistics
	  for(i=0;i<number;i++){
	    amount+=arr[i];
	  }
	  avg = amount/number;
	  return avg;
	 }else{
	  
	   if(arr[0]<arr[1]){
	    min = arr[0];max=arr[1];
	   }
	   else{
	     min=arr[1];max=arr[0];
	    }
	    
	 for(i=2;i<number;i++){
	  if(arr[i]<min){
	    amount+=min;  //arr<min
	    min=arr[i];
	  }else {
	    if(arr[i]>max){
	      amount+=max;  //arr>max
	      max=arr[i];
	    }else{
	      amount+=arr[i]; //min<=arr<=max
	    }
	  }//if

	 }//for

	 avg = (uint16_t)amount/(number-2);

	 }//if

	 return avg;
};

void Anemometre::updateAnemometre()
{
	static unsigned long samplingTime = millis();
	static uint16_t voltage;
	unsigned long tempsDebut;

	//if(millis()-samplingTime > _intervalMesure)
	//{
		//tableauAnemometre[indexAnemometre++]=
		_etatPin = digitalRead(_sensorPin);
		if(_etatPin == 1 ){
			nbTour=0;
    		tempsDebut=millis();
    		 while(millis()-tempsDebut < intervalleCalcul)
    		 {
    		 	int etat = digitalRead(5);
      			nbTour = (_etatPin !=  etat) ? nbTour+1 : nbTour; 
      			_etatPin = etat;
    		 }
    		tableauAnemometre[indexAnemometre++]=nbTour;//*2*3.14*7.2*0.01;
			if(indexAnemometre==_tailleEchantillon)
			{
				indexAnemometre=0;
			}
		/*for (int i = 0; i < _tailleEchantillon; ++i)
		{
			Serial.print(tableauAnemometre[i]);
			Serial.print(",");
			 code 
		}
		Serial.println();*/ 
		voltage = moyenne(tableauAnemometre, _tailleEchantillon);
		anemometreValue = voltage;
		//samplingTime=millis();
	//}
	}
};


