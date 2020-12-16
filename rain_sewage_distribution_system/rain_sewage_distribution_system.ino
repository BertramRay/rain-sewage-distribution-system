/*************************************************** 
rainwater and sewage separate system Beta 1.0
Designer: Bertram Ray
Design Date: 2020/12/10
All Rights Reserved


 ****************************************************/
//三通阀参数
#define pH_low_threshold = 4.0
#define pH_high_threshold = 10.0
#define tds_threshold = 1000
#define TU_threshold = 2500
#define triple_valve_pin = 12
//浊度传感器参数
float TU=0.0;
float TU_value=0.0;
float TU_calibration=0.0;
float temp_data=25.0;
float K_Value=3347.19;
//PH传感器参数
#define SensorPin A2            //pH meter Analog output to Arduino Analog Input 2
#define Offset 21.078           //deviation compensate
#define k -5.6241
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;  
//TDS传感器参数
#define TdsSensorPin A1
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);  
  pinMode(TdsSensorPin,INPUT);
  pinMode(triple_valve_pin,OUTPUT);
  Serial.print("欢迎使用雨污分流系统！该系统可以检测水体的pH,可溶性固体含量和浊度，自动进行雨污分流操作。")
}

void loop() {
  // put your main code here, to run repeatedly:
  //浊度传感器部分
  int sensorValue = analogRead(A0);// read the input on analog pin 0:
  float TU = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  TU_calibration=-0.0192*(temp_data-25)+TU;  
  TU_value=-865.68*TU_calibration + K_Value;
  
  if(TU_value<=0){TU_value=0;}
  if(TU_value>=3000){TU_value=3000;}
  Serial.print("水体浊度值:");
  Serial.print(TU_value); // print out the value you read:
  Serial.println("NTU");
  //pH传感器部分
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = k*voltage+Offset;
      if(pHValue<=0.0){pHValue=0.0;}
      if(pHValue>14.0){pHValue=14.0;}
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
//    Serial.print("Voltage:");
//    Serial.print(voltage,2);
    Serial.print("水体pH值: ");
    Serial.println(pHValue,2);
    digitalWrite(LED,digitalRead(LED)^1);
    printTime=millis();
  }
  //TDS传感器代码部分
   static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)     //every 40 milliseconds,read the analog value from the ADC
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
        analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
      float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      Serial.print("水体可溶性固体TDS值: ");
      Serial.print(tdsValue,0);
      Serial.println("ppm");
   }
   //三通阀开合代码
   if(TU_value>TU_threshold || pHValue<pH_low_threshold || pHValue>pH_high_threshold || tdsValue>tds_threshold){
    digitalWrite(triple_valve_pin, HIGH);
   }else{
    digitalWrite(triple_valve_pin, LOW);
   }
   delay(1000);
}

//pH传感器求均值代码
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
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
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

//TDS获取中位数代码
int getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
    bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
    for (i = 0; i < iFilterLen - j - 1; i++) 
          {
      if (bTab[i] > bTab[i + 1]) 
            {
    bTemp = bTab[i];
          bTab[i] = bTab[i + 1];
    bTab[i + 1] = bTemp;
       }
    }
      }
      if ((iFilterLen & 1) > 0)
  bTemp = bTab[(iFilterLen - 1) / 2];
      else
  bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}
