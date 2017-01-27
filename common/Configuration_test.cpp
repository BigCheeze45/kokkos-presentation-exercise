/********************************************************************
* Configuration_test driver file
*
* Created by Erman Gurses on 2/8/16.
* Modified by Rutuja Patil on 3/8/2016: Test6 added 
* Modified by Sarah Willer in June 2016: 
*     > Test class added to allow wrapped access to protected 
*       addParam methods
*     > Test7 added to test addParam calls to hasConflict()
* ********************************************************************/
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <sstream>

#include "Configuration.h"

using namespace std;
 
/***************************************************************************
*
*  to_string() function
*  
***************************************************************************/
template <typename T>
std::string to_string(T value)
{
        std::ostringstream os ;
        os << value ;
        return os.str() ;
}

/********************************************************************
* 
* validate function
*
********************************************************************/
int validate (string testType, string expectedString, string generatedString,
		       int test ){

    if (generatedString.compare(expectedString)){
      printf("*****%s Test %d*****\n",testType.c_str(),test);
      printf(" Expected: %s",expectedString.c_str());
      printf("Generated: %s\n",generatedString.c_str());
      printf("\nDo not Match!\n\n");
      return 0;
    }

    return 1;

}
        
int main(){

  int test_count = 0;
  int test_fail = 0;
  string _output = "Output";
  string _bool = "Bool";
  string _int = "Integer";
  string _string = "String";

  /****************************************************************************
  *  Test 1  ******************************************************************
  ****************************************************************************/
  int test = 1;
  const int N1 = 7;
  char * temp1[] = {"bin/test1",
                    "--Nx","150",
                    "--Ny","151,",
                    "-n",
          //          "--help",
                    "-v"};
  // Parse temp1
  Configuration config1;

  config1.addParamInt("Nx",'k',100,"--Nx <problem-size> for x-axis in elements (N)");
  config1.addParamInt("Ny",'l',100,"--Ny <problem-size> for y-axis in elements (N)");
  config1.addParamInt("Nz",'m',100,"--Nz <problem-size> for z-axis in elements (N)");

  config1.addParamInt("bx",'x',1,"--bx <block-size> for x-axis in elements");
  config1.addParamInt("by",'y',1,"--by <block-size> for y-axis in elements");
  config1.addParamInt("bz",'z',1,"--bz <block-size> for z-axis in elements");

  config1.addParamInt("tilex",'a',128,"--tilex <tile-size> for x-axis in elements");
  config1.addParamInt("tiley",'b',128,"--tiley <tile-size> for y-axis in elements");
  config1.addParamInt("tilez",'c',128,"--tilez <tile-size> for z-axis in elements");

  config1.addParamInt("T",'T',100,"-T <time-steps>, the number of time steps");
  config1.addParamInt("height",'H',-1,"height <#>, number of time steps in tile");
  config1.addParamInt("tau",'t',30,"--tau <tau>, distance between tiling"
                                "hyperplanes (all diamond(slab))");
  config1.addParamInt("num_threads",'p',1,"-p <num_threads>, number of cores");
  config1.addParamInt("global_seed", 'g', 1524, "--global_seed " 
                                           "<global_seed>, seed for rng");
 
  config1.addParamBool("n",'n', false, "-n do not print time");

  config1.parse(N1,temp1);
  string expectedString1 = "Executable:bin/test1,Nx:150,Ny:151,Nz:100,bx:1,"
                           "by:1,bz:1,tilex:128,tiley:128,tilez:128,T:100,"
                           "height:-1,tau:30,num_threads:1,global_seed:1524,";
  // Get the generated string
  string generatedString1 = config1.toLDAPString();
  // Validate generated string
  test_count++;
  if(!validate(_output,expectedString1,generatedString1,test)){
    test_fail++;
  }

  // Check bool values using getBool() function
  string generatedBoolString1 = to_string(config1.getBool("help")) + 
                                to_string(config1.getBool("n")) +
		                to_string(config1.getBool("v"));
  string expectedBoolString1 = "011";
  test_count++;
  if(!validate(_bool,expectedBoolString1,generatedBoolString1,test)){
    test_fail++;
  }

  // Check expectedString1 using getInt() function
  string generatedIntString1 = "Executable:bin/test1"
                   ",Nx:"+ to_string(config1.getInt("Nx")) +
                   ",Ny:"+ to_string(config1.getInt("Ny")) +
                   ",Nz:"+ to_string(config1.getInt("Nz")) +
                   ",bx:"+ to_string(config1.getInt("bx")) +
                   ",by:"+ to_string(config1.getInt("by")) +
                   ",bz:"+ to_string(config1.getInt("bz")) +
                   ",tilex:"+ to_string(config1.getInt("tilex")) +
                   ",tiley:"+ to_string(config1.getInt("tiley")) +
                   ",tilez:"+ to_string(config1.getInt("tilez")) +
                   ",T:"+ to_string(config1.getInt("T")) +
                   ",height:"+ to_string(config1.getInt("height")) +
                   ",tau:"+ to_string(config1.getInt("tau")) +
                   ",num_threads:"+ to_string(config1.getInt("num_threads"))+
                   ",global_seed:"+ to_string(config1.getInt("global_seed"))+
                   ",";
  test_count++;
  if(!validate(_int,expectedString1,generatedIntString1,test)){
    test_fail++;
  }


  /****************************************************************************
  *  Test 2  ******************************************************************
  ****************************************************************************/
  test = 2;
  const int N2 = 27;
  optind = 0;
  char * temp2[] = {"bin/test2",
                    "--Nx","250",
                    "--Ny","251",
                    "--Nz","252",
                    "--bx","253",
                    "--by","254",
                    "--bz","255",
                    "--tilez","258",
                    "--tilex","256",
                    "--tiley","257",
                    "-T","259",
                    "--height","260",
                    "--tau","261",
                    "-p","262",
         //           "--help"
                    };
  // Parse temp2
  Configuration config2;

  config2.addParamInt("Nx",'k',100,"--Nx <problem-size> for x-axis in elements (N)");
  config2.addParamInt("Ny",'l',100,"--Ny <problem-size> for y-axis in elements (N)");
  config2.addParamInt("Nz",'m',100,"--Nz <problem-size> for z-axis in elements (N)");

  config2.addParamInt("bx",'x',1,"--bx <block-size> for x-axis in elements");
  config2.addParamInt("by",'y',1,"--by <block-size> for y-axis in elements");
  config2.addParamInt("bz",'z',1,"--bz <block-size> for z-axis in elements");

  config2.addParamInt("tilex",'a',128,"--tilex <tile-size> for x-axis in elements");
  config2.addParamInt("tiley",'b',128,"--tiley <tile-size> for y-axis in elements");
  config2.addParamInt("tilez",'c',128,"--tilez <tile-size> for z-axis in elements");

  config2.addParamInt("T",'T',100,"-T <time-steps>, the number of time steps");
  config2.addParamInt("height",'H',-1,"height <#>, number of time steps in tile");
  config2.addParamInt("tau",'t',30,"--tau <tau>, distance between tiling"
                                "hyperplanes (all diamond(slab))");
  config2.addParamInt("num_threads",'p',1,"-p <num_threads>, number of cores");
  config2.addParamInt("global_seed", 'g', 1524, "--global_seed " 
                                           "<global_seed>, seed for rng");
 
  config2.addParamBool("n",'n', false, "-n do not print time");

  config2.parse(N2,temp2);

  string expectedString2 = "Executable:bin/test2,Nx:250,Ny:251,Nz:252,bx:253,"
                           "by:254,bz:255,tilex:256,tiley:257,tilez:258,T:259"
                      ",height:260,tau:261,num_threads:262,global_seed:1524,";
  // Get the generated string
  string generatedString2 = config2.toLDAPString();
  // Validate generated string
  test_count++;
  if(!validate(_output,expectedString2,generatedString2,test)){
    test_fail++;
  }

  string generatedBoolString2 = to_string(config2.getBool("help")) +
		                        to_string(config2.getBool("n"))    +
		                        to_string(config2.getBool("v"));
  string expectedBoolString2 = "000";

  test_count++;
  if(!validate(_bool,expectedBoolString2,generatedBoolString2,test)){
    test_fail++;
  }

  // Check expectedString2 using getInt() function
  string generatedIntString2 = "Executable:bin/test2"
                   ",Nx:"+ to_string(config2.getInt("Nx")) +
                   ",Ny:"+ to_string(config2.getInt("Ny")) +
                   ",Nz:"+ to_string(config2.getInt("Nz")) +
                   ",bx:"+ to_string(config2.getInt("bx")) +
                   ",by:"+ to_string(config2.getInt("by")) +
                   ",bz:"+ to_string(config2.getInt("bz")) +
                   ",tilex:"+ to_string(config2.getInt("tilex")) +
                   ",tiley:"+ to_string(config2.getInt("tiley")) +
                   ",tilez:"+ to_string(config2.getInt("tilez")) +
                   ",T:"+ to_string(config2.getInt("T")) +
                   ",height:"+ to_string(config2.getInt("height")) +
                   ",tau:"+ to_string(config2.getInt("tau")) +
                   ",num_threads:"+ to_string(config2.getInt("num_threads"))+
                   ",global_seed:"+ to_string(config2.getInt("global_seed"))+
                   ",";
  test_count++;
  if(!validate(_int,expectedString2,generatedIntString2,test)){
    test_fail++;
  }

  /****************************************************************************
  *  Test 3  ******************************************************************
  ****************************************************************************/
  test = 3;
  optind = 0;
  const int N3 = 14;
  char * temp3[] = {"bin/test3",
                    "--Nx","350",
                    "--bz","351",
                    "--tilex","352",
                    "--tiley","353",
                    "--tilez","354",
                    "-p","355",
                    "-n"};
  // Parse temp3
  Configuration config3;

  config3.addParamInt("Nx",'k',100,"--Nx <problem-size> for x-axis in elements (N)");
  config3.addParamInt("Ny",'l',100,"--Ny <problem-size> for y-axis in elements (N)");
  config3.addParamInt("Nz",'m',100,"--Nz <problem-size> for z-axis in elements (N)");

  config3.addParamInt("bx",'x',1,"--bx <block-size> for x-axis in elements");
  config3.addParamInt("by",'y',1,"--by <block-size> for y-axis in elements");
  config3.addParamInt("bz",'z',1,"--bz <block-size> for z-axis in elements");

  config3.addParamInt("tilex",'a',128,"--tilex <tile-size> for x-axis in elements");
  config3.addParamInt("tiley",'b',128,"--tiley <tile-size> for y-axis in elements");
  config3.addParamInt("tilez",'c',128,"--tilez <tile-size> for z-axis in elements");

  config3.addParamInt("T",'T',100,"-T <time-steps>, the number of time steps");
  config3.addParamInt("height",'H',-1,"height <#>, number of time steps in tile");
  config3.addParamInt("tau",'t',30,"--tau <tau>, distance between tiling"
                                "hyperplanes (all diamond(slab))");
  config3.addParamInt("num_threads",'p',1,"-p <num_threads>, number of cores");
  config3.addParamInt("global_seed", 'g', 1524, "--global_seed " 
                                           "<global_seed>, seed for rng");
 
  config3.addParamBool("n",'n', false, "-n do not print time");

  config3.parse(N3,temp3);

  string expectedString3 = "Executable:bin/test3,Nx:350,Ny:100,Nz:100,bx:1,by"
                           ":1,bz:351,tilex:352,tiley:353,tilez:354,T:100,hei"
                           "ght:-1,tau:30,num_threads:355,global_seed:1524,";
  // Get the generated string
  string generatedString3 = config3.toLDAPString();
  // Validated generated string

  test_count++;
  if(!validate(_output,expectedString3,generatedString3,test)){
    test_fail++;
  }

  string generatedBoolString3 = to_string(config3.getBool("help")) +
		                        to_string(config3.getBool("n"))    +
		                        to_string(config3.getBool("v"));
  string expectedBoolString3 = "010";
  test_count++;
  if(!validate(_bool,expectedBoolString3,generatedBoolString3,test)){
    test_fail++;
  }

  // Check expectedString3 using getInt() function
  string generatedIntString3 = "Executable:bin/test3"
                   ",Nx:"+ to_string(config3.getInt("Nx")) +
                   ",Ny:"+ to_string(config3.getInt("Ny")) +
                   ",Nz:"+ to_string(config3.getInt("Nz")) +
                   ",bx:"+ to_string(config3.getInt("bx")) +
                   ",by:"+ to_string(config3.getInt("by")) +
                   ",bz:"+ to_string(config3.getInt("bz")) +
                   ",tilex:"+ to_string(config3.getInt("tilex")) +
                   ",tiley:"+ to_string(config3.getInt("tiley")) +
                   ",tilez:"+ to_string(config3.getInt("tilez")) +
                   ",T:"+ to_string(config3.getInt("T")) +
                   ",height:"+ to_string(config3.getInt("height")) +
                   ",tau:"+ to_string(config3.getInt("tau")) +
                   ",num_threads:"+ to_string(config3.getInt("num_threads"))+
                   ",global_seed:"+ to_string(config3.getInt("global_seed"))+
                   ",";

  test_count++;
  if(!validate(_int,expectedString3,generatedIntString3,test)){
    test_fail++;
  }

  /****************************************************************************
  *  Test 4  ******************************************************************
  ****************************************************************************/
  test = 4;
  optind = 0;
  const int N4 = 14;
  char * temp4[] = {"bin/test4",
                    "-T","450",
                    "-p","451",
                    "--tau","452",
                    "--bx","453",
                    "--by","454",
                    "--bz","455",
                    "-v"};
  // Parse temp4
  Configuration config4;

  config4.addParamInt("Nx",'k',100,"--Nx <problem-size> for x-axis in elements (N)");
  config4.addParamInt("Ny",'l',100,"--Ny <problem-size> for y-axis in elements (N)");
  config4.addParamInt("Nz",'m',100,"--Nz <problem-size> for z-axis in elements (N)");

  config4.addParamInt("bx",'x',1,"--bx <block-size> for x-axis in elements");
  config4.addParamInt("by",'y',1,"--by <block-size> for y-axis in elements");
  config4.addParamInt("bz",'z',1,"--bz <block-size> for z-axis in elements");

  config4.addParamInt("tilex",'a',128,"--tilex <tile-size> for x-axis in elements");
  config4.addParamInt("tiley",'b',128,"--tiley <tile-size> for y-axis in elements");
  config4.addParamInt("tilez",'c',128,"--tilez <tile-size> for z-axis in elements");

  config4.addParamInt("T",'T',100,"-T <time-steps>, the number of time steps");
  config4.addParamInt("height",'H',-1,"height <#>, number of time steps in tile");
  config4.addParamInt("tau",'t',30,"--tau <tau>, distance between tiling"
                                "hyperplanes (all diamond(slab))");
  config4.addParamInt("num_threads",'p',1,"-p <num_threads>, number of cores");
  config4.addParamInt("global_seed", 'g', 1524, "--global_seed " 
                                           "<global_seed>, seed for rng");
 
  config4.addParamBool("n",'n', false, "-n do not print time");

  config4.parse(N4,temp4);
  // Expected string
  string expectedString4 = "Executable:bin/test4,Nx:100,Ny:100,Nz:100,bx:453,"
                           "by:454,bz:455,tilex:128,tiley:128,tilez:128,T:450"
                      ",height:-1,tau:452,num_threads:451,global_seed:1524,";
  // Get the generated string
  string generatedString4 = config4.toLDAPString();

  // Validate generated string
  test_count++;
  if(!validate(_output,expectedString4,generatedString4,test)){
    test_fail++;
  }

  string generatedBoolString4 = to_string(config4.getBool("help")) +
		                        to_string(config4.getBool("n"))    +
		                        to_string(config4.getBool("v"));
  string expectedBoolString4 = "001";

  test_count++;
  if(!validate(_bool,expectedBoolString4,generatedBoolString4,test)){
    test_fail++;
  }

  // Check expectedString4 using getInt() function
  string generatedIntString4 = "Executable:bin/test4"
                   ",Nx:"+ to_string(config4.getInt("Nx")) +
                   ",Ny:"+ to_string(config4.getInt("Ny")) +
                   ",Nz:"+ to_string(config4.getInt("Nz")) +
                   ",bx:"+ to_string(config4.getInt("bx")) +
                   ",by:"+ to_string(config4.getInt("by")) +
                   ",bz:"+ to_string(config4.getInt("bz")) +
                   ",tilex:"+ to_string(config4.getInt("tilex")) +
                   ",tiley:"+ to_string(config4.getInt("tiley")) +
                   ",tilez:"+ to_string(config4.getInt("tilez")) +
                   ",T:"+ to_string(config4.getInt("T")) +
                   ",height:"+ to_string(config4.getInt("height")) +
                   ",tau:"+ to_string(config4.getInt("tau")) +
                   ",num_threads:"+ to_string(config4.getInt("num_threads"))+
                   ",global_seed:"+ to_string(config4.getInt("global_seed"))+
                   ",";
  test_count++;
  if(!validate(_int,expectedString4,generatedIntString4,test)){
    test_fail++;
  }

  /****************************************************************************
  *  Test 5  ******************************************************************
  ****************************************************************************/
  test = 5;
  optind = 0;
  const int N5 = 22;
  char * temp5[] = {"bin/test5",
		             "-n",
                     "--tau","551",
                     "-p","552",
                     "--bx","553",
                     "--by","554",
                     "--bz","555",
                     "-T","556",
                     "--Nx","557",
                     "--Ny","558",
                     "--Nz","559",
            //         "--help",
                     "--global_seed","560"};
  // Parse temp5
  Configuration config5;

  config5.addParamInt("Nx",'k',100,"--Nx <problem-size> for x-axis in elements (N)");
  config5.addParamInt("Ny",'l',100,"--Ny <problem-size> for y-axis in elements (N)");
  config5.addParamInt("Nz",'m',100,"--Nz <problem-size> for z-axis in elements (N)");

  config5.addParamInt("bx",'x',1,"--bx <block-size> for x-axis in elements");
  config5.addParamInt("by",'y',1,"--by <block-size> for y-axis in elements");
  config5.addParamInt("bz",'z',1,"--bz <block-size> for z-axis in elements");

  config5.addParamInt("tilex",'a',128,"--tilex <tile-size> for x-axis in elements");
  config5.addParamInt("tiley",'b',128,"--tiley <tile-size> for y-axis in elements");
  config5.addParamInt("tilez",'c',128,"--tilez <tile-size> for z-axis in elements");

  config5.addParamInt("T",'T',100,"-T <time-steps>, the number of time steps");
  config5.addParamInt("height",'H',-1,"height <#>, number of time steps in tile");
  config5.addParamInt("tau",'t',30,"--tau <tau>, distance between tiling"
                                "hyperplanes (all diamond(slab))");
  config5.addParamInt("num_threads",'p',1,"-p <num_threads>, number of cores");
  config5.addParamInt("global_seed", 'g', 1524, "--global_seed " 
                                           "<global_seed>, seed for rng");
 
  config5.addParamBool("n",'n', false, "-n do not print time");

  config5.parse(N5,temp5);
  // Expected string
  string expectedString5 = "Executable:bin/test5,Nx:557,Ny:558,Nz:559,bx:553,"
                           "by:554,bz:555,tilex:128,tiley:128,tilez:128,T:556"
                        ",height:-1,tau:551,num_threads:552,global_seed:560,";

  // Get the generated string
  string generatedString5 = config5.toLDAPString();
  // Validate generated string
  test_count++;
  if(!validate(_output,expectedString5,generatedString5,test)){
    test_fail++;
  }

  string generatedBoolString5 = to_string(config5.getBool("help")) +
		                        to_string(config5.getBool("n"))    +
		                        to_string(config5.getBool("v"));
  string expectedBoolString5 = "010";
  test_count++;
  if(!validate(_bool,expectedBoolString5,generatedBoolString5,test)){
    test_fail++;
  }

  // Check expectedString5 using getInt() function
  string generatedIntString5 = "Executable:bin/test5"
                   ",Nx:"+ to_string(config5.getInt("Nx")) +
                   ",Ny:"+ to_string(config5.getInt("Ny")) +
                   ",Nz:"+ to_string(config5.getInt("Nz")) +
                   ",bx:"+ to_string(config5.getInt("bx")) +
                   ",by:"+ to_string(config5.getInt("by")) +
                   ",bz:"+ to_string(config5.getInt("bz")) +
                   ",tilex:"+ to_string(config5.getInt("tilex")) + 
                   ",tiley:"+ to_string(config5.getInt("tiley")) +
                   ",tilez:"+ to_string(config5.getInt("tilez")) +
                   ",T:"+ to_string(config5.getInt("T")) +
                   ",height:"+ to_string(config5.getInt("height")) +
                   ",tau:"+ to_string(config5.getInt("tau")) +
                   ",num_threads:"+ to_string(config5.getInt("num_threads"))+
                   ",global_seed:"+ to_string(config5.getInt("global_seed"))+
                   ",";

  test_count++;
  if(!validate(_int,expectedString5,generatedIntString5,test)){
    test_fail++;
  }

  /****************************************************************************
  *  Test 7  ******************************************************************
  *****************************************************************************
  *  Test error checking that should prevent duplicate parameter options from 
  *  being added through the addParam methods. Error checking is performed by 
  *  the hasConflict method, which is called from each of the addParam methods. 
  *  hasConflict throws an exception if the values passed to fieldname and/or 
  *  single_char already exist in mLongOptions, or returns false if the values 
  *  are unique.
  *
  *  This section contains 18 tests, six tests for each addParam method. 
  ****************************************************************************/

  test = 7;
  optind = 0;
  const int N7 = 7; 
  char * temp7[] = {"bin/test7",
                    "--Nx","150",
                    "--Ny","151,",
                    "-n",
           //         "--help",
                    "-v"};
  // Parse temp7
  Configuration config7; 

  config7.addParamInt("Nx",'k',100,"--Nx <problem-size> for x-axis in elements (N)");
  config7.addParamInt("Ny",'l',100,"--Ny <problem-size> for y-axis in elements (N)");
  config7.addParamInt("Nz",'m',100,"--Nz <problem-size> for z-axis in elements (N)");

  config7.addParamInt("bx",'x',1,"--bx <block-size> for x-axis in elements");
  config7.addParamInt("by",'y',1,"--by <block-size> for y-axis in elements");
  config7.addParamInt("bz",'z',1,"--bz <block-size> for z-axis in elements");

  config7.addParamInt("tilex",'a',128,"--tilex <tile-size> for x-axis in elements");
  config7.addParamInt("tiley",'b',128,"--tiley <tile-size> for y-axis in elements");
  config7.addParamInt("tilez",'c',128,"--tilez <tile-size> for z-axis in elements");

  config7.addParamInt("T",'T',100,"-T <time-steps>, the number of time steps");
  config7.addParamInt("height",'H',-1,"height <#>, number of time steps in tile");
  config7.addParamInt("tau",'t',30,"--tau <tau>, distance between tiling"
                                "hyperplanes (all diamond(slab))");
  config7.addParamInt("num_threads",'p',1,"-p <num_threads>, number of cores");
  config7.addParamInt("global_seed", 'g', 1524, "--global_seed " 
                                           "<global_seed>, seed for rng");
 
  config7.addParamBool("n",'n', false, "-n do not print time");

  config7.parse(N7,temp7);
 
  std::string fieldname = "alpha";
  char single_char = 'A';
  std::string help_str = "--this is a helpful comment";
  int initInt = 3;
  bool initBool = false;
  std::string initStr = "moon";

  /*  TESTS FOR addParamInt  ************************************************/
  /*  Test exception in addParamInt on duplicate fieldname  *****************/
  test_count++;
  // NO EXCEPTION EXPECTED
  // fieldname: alpha, single_char: A
  try { 
      config7.addParamInt(fieldname, single_char, initInt, help_str);
      printf("TEST PASS: No exception thrown, none expected: fieldname addParamInt\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++; 
      printf("TEST FAIL: Unexpected exception: fieldname addParamInt\n");
  }
  test_count++;
  single_char = 'B';
  // EXCEPTION EXPECTED -- duplicate fieldname
  // fieldname: alpha, single_char: B
  try { 
      config7.addParamInt(fieldname, single_char, initInt, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: fieldname addParamInt\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: fieldname addParamInt\n");
  }
   
  /*  Test exception in addParamInt on duplicate single_char  ***************/
  test_count++;
  fieldname = "charlie";
  single_char = 'C';
  // NO EXCEPTION EXPECTED
  // fieldname: charlie, single_char: C
  try {
      config7.addParamInt(fieldname, single_char, initInt, help_str);
      printf("TEST PASS: No exception thrown, none expected: single_char addParamInt\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++;
      printf("TEST FAIL: Unexpected exception: single_char addParamInt\n");
  }
  test_count++;
  fieldname = "delta";
  // EXCEPTION EXPECTED -- duplicate single_char
  // fieldname: delta, command char: C
  try {
      config7.addParamInt(fieldname, single_char, initInt, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: single_char addParamInt\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: single_char addParamInt\n");
  }
   
  /*  Test exception in addParamInt on duplicate fieldname and single_char  */
  test_count++;
  fieldname = "echo";
  single_char = 'E';
  // NO EXCEPTION EXPECTED
  // fieldname: echo, single_char: E
  try {
      config7.addParamInt(fieldname, single_char, initInt, help_str);
      printf("TEST PASS: No exception thrown, none expected: fieldname and single_char addParamInt\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++;
      printf("TEST FAIL: Unexpected exception: fieldname and single_char addParamInt\n");
  }
  test_count++;
  // EXCEPTION EXPECTED -- duplicate fieldname and single_char
  // fieldname: echo, single_char: E
  try {
      config7.addParamInt(fieldname, single_char, initInt, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: fieldname and single_char addParamInt\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: fieldname and single_char addParamInt\n");
  }
   
  /*  TESTS FOR addParamBool  ***********************************************/
  /*  Test exception in addParamBool on duplicate fieldname  ****************/
  test_count++;
  fieldname = "foxtrot";
  single_char = 'F';
  // NO EXCEPTION EXPECTED
  // fieldname: foxtrot, single_char: F
  try { 
      config7.addParamBool(fieldname, single_char, initBool, help_str);
      printf("TEST PASS: No exception thrown, none expected: fieldname addParamBool\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++; 
      printf("TEST FAIL: Unexpected exception: fieldname addParamBool\n");
  }
  test_count++;
  single_char = 'G';
  // EXCEPTION EXPECTED -- duplicate fieldname
  // fieldname: foxtrot, single_char: G
  try { 
      config7.addParamBool(fieldname, single_char, initBool, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: fieldname addParamBool\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: fieldname addParamBool\n");
  }
   
  /*  Test exception in addParamBool on duplicate single_char  **************/
  test_count++;
  fieldname = "hotel";
  single_char = 'H';
  // NO EXCEPTION EXPECTED
  // fieldname: hotel, single_char: H
  try {
      config7.addParamBool(fieldname, single_char, initBool, help_str);
      // this throws exception on newly capitalized H for height
      test_fail++;
      printf("TEST FAIL: No exception thrown:: single_char addParamBool\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: single_char addParamBool\n");
  }
  test_count++;
  fieldname = "india";
  // EXCEPTION EXPECTED -- duplicate single_char
  // fieldname: india, command char: H
  try {
      config7.addParamBool(fieldname, single_char, initBool, help_str);
       
      printf("TEST FAIL: No exception thrown: single_char addParamBool\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: single_char addParamBool\n");
  }
   
  /*  Test exception in addParamBool on duplicate fieldname and single_char  */
  test_count++;
  fieldname = "juliet";
  single_char = 'J';
  // NO EXCEPTION EXPECTED
  // fieldname: juliet, single_char: J
  try {
      config7.addParamBool(fieldname, single_char, initBool, help_str);
      printf("TEST PASS: No exception thrown, none expected: fieldname and single_char addParamBool\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++;
      printf("TEST FAIL: Unexpected exception: fieldname and single_char addParamBool\n");
  }
  test_count++;
  // EXCEPTION EXPECTED -- duplicate fieldname and single_char
  // fieldname: juliet, single_char: J
  try {
      config7.addParamBool(fieldname, single_char, initBool, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: fieldname and single_char addParamBool\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: fieldname and single_char addParamBool\n");
  }
   
  /*  TESTS FOR addParamString  *********************************************/
  /*  Test exception in addParamString on duplicate fieldname  **************/
  test_count++;
  fieldname = "kilo";
  single_char = 'K';
  // NO EXCEPTION EXPECTED
  // fieldname: kilo, single_char: K
  try { 
      config7.addParamString(fieldname, single_char, initStr, help_str);
      printf("TEST PASS: No exception thrown, none expected: fieldname addParamString\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++; 
      printf("TEST FAIL: Unexpected exception: fieldname addParamString\n");
  }
  test_count++;
  single_char = 'L';
  // EXCEPTION EXPECTED -- duplicate fieldname
  // fieldname: kilo, single_char: L
  try { 
      config7.addParamString(fieldname, single_char, initStr, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: fieldname addParamString\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: fieldname addParamString\n");
  }
   
  /*  Test exception in addParamInt on duplicate single_char  ***************/
  test_count++;
  fieldname = "michael";
  single_char = 'M';
  // NO EXCEPTION EXPECTED
  // fieldname: michael, single_char: M
  try {
      config7.addParamString(fieldname, single_char, initStr, help_str);
      printf("TEST PASS: No exception thrown, none expected: single_char addParamString\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++;
      printf("TEST FAIL: Unexpected exception: single_char addParamString\n");
  }
  test_count++;
  fieldname = "november";
  // EXCEPTION EXPECTED -- duplicate single_char
  // fieldname: november, command char: M
  try {
      config7.addParamString(fieldname, single_char, initStr, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: single_char addParamString\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: single_char addParamString\n");
  }
   
  /*  Test exception in addParamString on duplicate fieldname and single_char  */
  test_count++;
  fieldname = "oscar";
  single_char = 'O';
  // NO EXCEPTION EXPECTED
  // fieldname: oscar, single_char: O
  try {
      config7.addParamString(fieldname, single_char, initStr, help_str);
      printf("TEST PASS: No exception thrown, none expected: fieldname and single_char addParamString\n");
  }
  catch (const std::invalid_argument& e) {
      test_fail++;
      printf("TEST FAIL: Unexpected exception: fieldname and single_char addParamString\n");
  }
  test_count++;
  // EXCEPTION EXPECTED -- duplicate fieldname and single_char
  // fieldname: oscar, single_char: O
  try {
      config7.addParamString(fieldname, single_char, initStr, help_str);
      test_fail++; 
      printf("TEST FAIL: No exception thrown: fieldname and single_char addParamString\n");
  }
  catch (const std::invalid_argument& e) {
      printf("TEST PASS: Expected exception thrown: fieldname and single_char addParamString\n");
  }
   
      
  /*****************************************************************************
  *  show test results  ********************************************************
  *****************************************************************************/

  if(test_fail){
    printf("*************** FAILURE %d of %d tests FAILED **********\n\n",
           test_fail,test_count);
  }

  return 0;
}


