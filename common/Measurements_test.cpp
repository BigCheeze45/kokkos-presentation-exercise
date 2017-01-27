//Created by Erman Gurses on 2/8/16.
/*****************************************************************************
 * Measurements_test driver file
 *
 ****************************************************************************/

#include <iostream>
#include <map>
#include <string>

#include "Measurements.h"

using namespace std;
/*****************************************************************************
 * validate function
 *
 ****************************************************************************/
int validate (string expectedString, string generatedString, int test ){

    if (generatedString.compare(expectedString)){
      printf("*****Test %d*****\n",test);
      printf(" Expected: %s\n",expectedString.c_str());
      printf("Generated: %s\n",generatedString.c_str());
      printf("Do not Match!\n\n");
      return 0;
    }
    return 1;
}
using namespace std;

int main(int argc, char* argv[]){

  int test_count = 0;
  int test_fail = 0;
  float data1 = 15.9;
  float data2 = 13.4;
  float data3 = 0.43435;
  float data4 = 54.45454;
  float data5 = 4343.43434;
  int   data6 = 345;
  int   data7 = 345335;
  int   data8 = 55434535;

    // *****Test 1*****
  Measurements measurement1;
  measurement1.setField("DataTransferFromDevice",data3);
  measurement1.setField("ExecutionTime",12.4354f);
  measurement1.setField("TotalTime",13.4f);
  measurement1.setField("DataTransferToDevice",14.3454f);
  measurement1.setField("Processing",data5);
  measurement1.setField("GlobalToLocalMemory",13234);
  measurement1.setField("LocalToGlobalMemory",13242334);

  string generatedString1 = measurement1.toLDAPString();
  string expectedString1 = "GlobalToLocalMemory:13234,LocalToGlobalMemory:132"
                       "42334,DataTransferFromDevice:0.434350,DataTransfe"
                       "rToDevice:14.345400,ExecutionTime:12.435400,Proce"
                       "ssing:4343.434570,TotalTime:13.400000,";
  // Validate generated string
  test_count++;
  if(!validate(expectedString1,generatedString1, test_count)){
    test_fail++;
  }

  // *****Test 2*****
  Measurements measurement2;
  measurement2.setField("TotalTime",data1);
  measurement2.setField("DataTransferToDevice",data7);
  measurement2.setField("Processing",data2);
  measurement2.setField("GlobalToLocalMemory",data6);
  measurement2.setField("DataTransferFromDevice",data6);
  measurement2.setField("ExecutionTime",data4);
  measurement2.setField("LocalToGlobalMemory",data8);

  string generatedString2 = measurement2.toLDAPString();
  string expectedString2 = "DataTransferFromDevice:345,DataTransferToDevice:3"
                       "45335,GlobalToLocalMemory:345,LocalToGlobalMemory"
                       ":55434535,ExecutionTime:54.454540,Processing:13.4"
                       "00000,TotalTime:15.900000,";
  // Validate generated string
  test_count++;
  if(!validate(expectedString2,generatedString2, test_count)){
    test_fail++;
  }  

    // *****Test 3*****
  Measurements measurement3;
  measurement3.setField("DataTransferFromDevice",data6);
  measurement3.setField("ExecutionTime",data4);
  measurement3.setField("Processing",data2);
  measurement3.setField("GlobalToLocalMemory",data6);
  measurement3.setField("TotalTime",data1);
  measurement3.setField("DataTransferToDevice",data7);
  measurement3.setField("LocalToGlobalMemory",data8);

  string generatedString3 = measurement3.toLDAPString();
  string expectedString3 = "DataTransferFromDevice:345,DataTransferToDevice:3"
                       "45335,GlobalToLocalMemory:345,LocalToGlobalMemory"
                       ":55434535,ExecutionTime:54.454540,Processing:13.4"
                       "00000,TotalTime:15.900000,";
  // Validate generated string
  test_count++;
  if(!validate(expectedString3,generatedString3, test_count)){
    test_fail++;
  }  

    // *****Test 4*****
  Measurements measurement4;
  measurement4.setField("Validation","SUCCESS");
  measurement4.setField("DataTransferFromDevice",data6);
  measurement4.setField("ExecutionTime",data4);
  measurement4.setField("Processing",data2);
  measurement4.setField("DataTransferToDevice",data7);
  measurement4.setField("LocalToGlobalMemory",data8);
  measurement4.setField("ExecutionStatus","SUCCESS");


  string generatedString4 = measurement4.toLDAPString();
  string expectedString4 = "DataTransferFromDevice:345,DataTransferToDevice:3"
                       "45335,LocalToGlobalMemory:55434535,ExecutionTime"
                       ":54.454540,Processing:13.400000,ExecutionStatus:S"
                       "UCCESS,Validation:SUCCESS,";
  // Validate generated string
  test_count++;
  if(!validate(expectedString4,generatedString4, test_count)){
    test_fail++;
  }

  // *****Test 5*****
  Measurements measurement5;
  measurement5.setField("Validation","SUCCESS");
  measurement5.setField("DataTransferFromDevice",data6);
  measurement5.setField("ExecutionTime",data4);
  measurement5.setField("Processing",data2);
  measurement5.setField("DataTransferToDevice",data7);
  measurement5.setField("LocalToGlobalMemory",data8);
  measurement5.setField("ExecutionStatus","SUCCESS");

  // Generate string using getField method
  string generatedString5 ="DataTransferFromDevice:"+
           to_string(measurement5.getFieldInt("DataTransferFromDevice"))+
           ",DataTransferToDevice:"+
           to_string(measurement5.getFieldInt("DataTransferToDevice"))+
           ",LocalToGlobalMemory:"+
           to_string(measurement5.getFieldInt("LocalToGlobalMemory"))+
           ",ExecutionTime:"+
           to_string(measurement5.getFieldFloat("ExecutionTime"))+
           ",Processing:"+
           to_string(measurement5.getFieldFloat("Processing"))+
           ",ExecutionStatus:"+
           measurement5.getFieldString("ExecutionStatus")+
           ",Validation:"+
           measurement5.getFieldString("Validation") + ",";

  string expectedString5 = "DataTransferFromDevice:345,DataTransferToDevice:3"
                     "45335,LocalToGlobalMemory:55434535,ExecutionTime"
                     ":54.454540,Processing:13.400000,ExecutionStatus:S"
                     "UCCESS,Validation:SUCCESS,";
  // Validate generated string
  test_count++;
  if(!validate(expectedString5,generatedString5, test_count)){
    test_fail++;
  }
  
    // *****Test 6*****
  Measurements measurement6;
  measurement6.setField("Validation","SUCCESS");
  measurement6.setField("DataTransferFromDevice",data6);
  measurement6.setField("ExecutionTime",data4);
  measurement6.setField("Processing",data2);
  measurement6.setField("DataTransferToDevice",data7);
  measurement6.setField("LocalToGlobalMemory",data8);
  measurement6.setField("ExecutionStatus","SUCCESS");

  string expectedString6 = "DataTransferFromDevice:345,DataTransferToDevice:3"
                     "45335,LocalToGlobalMemory:55434535,ExecutionTime"
                     ":54.454540,Processing:13.400000,ExecutionStatus:S"
                     "UCCESS,Validation:SUCCESS,";
                     
  string generatedString6 = measurement6.toLDAPString();                     
                     
  // Validate generated string
  test_count++;
  if(!validate(expectedString6,generatedString6, test_count)){
    test_fail++;
  }
  
  if(test_fail){
    printf("*************** FAILURE %d of %d tests FAILED **********\n\n",
           test_fail,test_count);
  }

  
  return 0;
}


