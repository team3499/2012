#include "OI.h"

OI::OI()
{
  // Even if there are two joysticks with the same init,
  // it wont affect end result, just waste memory
  js[JOYSTICK_ARRAY_DRIVE] = new Joystick(JOYSTICK_INIT_DRIVE);
  js[JOYSTICK_ARRAY_ACCESSORY] = new Joystick(JOYSTICK_INIT_ACCESSORY);
  //should use the JOYSTICK_COUNT here
  js[2] = ( 2+1>JOYSTICK_COUNT ? NULL : new Joystick(2+1)); //new Joystick(1); We dont have a third joystick
  js[3] = ( 3+1>JOYSTICK_COUNT ? NULL : new Joystick(3+1)); //new Joystick(1); We dont have a fourth joystick
  //preferences = Preferences::GetInstance();
}

// For now, maybe it will change, These numbers START AT 1
bool OI::GetRawButton(int js, UINT32 button){
  if(js-1 > JOYSTICK_COUNT){
    printf("Joystick out of range in OI::GetRawButton: value: %d",js);
    return (bool)NULL;
  }
  return this->js[js-1]->GetRawButton(button);
}

// For now, maybe it will change, These numbers START AT 1
float OI::GetY(int js){
  if(js-1 > JOYSTICK_COUNT){
    printf("Joystick out of range in OI::GetY: value: %d",js);
    return (float)NULL;
  }
  return this->js[js-1]->GetY();
}

// For now, maybe it will change, These numbers START AT 1
float OI::GetX(int js){
  if(js-1 > JOYSTICK_COUNT){
    printf("Joystick out of range in OI::GetX: value: %d",js);
    return (float)NULL;
  }
  return this->js[js-1]->GetX();
}

// For now, maybe it will change, These numbers START AT 1
float OI::GetZ(int js){
  if(js-1 > JOYSTICK_COUNT){
    printf("Joystick out of range in OI::GetZ: value: %d",js);
    return (float)NULL;
  }
  return this->js[js-1]->GetZ();
}

// For now, maybe it will change, These numbers START AT 1
bool OI::GetTrigger(int js){
  if(js-1 > JOYSTICK_COUNT){
    printf("Joystick out of range in OI::GetTrigger: value: %d",js);
    return (bool)NULL;
  }
  return this->js[js-1]->GetTrigger();
}

//Gets the drive Joystick
Joystick *OI::GetDriveJS(){
  return js[JOYSTICK_ARRAY_DRIVE];
}

//Gets the accessory Joystick
Joystick *OI::GetAccessoryJS(){
  return js[JOYSTICK_ARRAY_ACCESSORY];
}
/********************************\
 *      Preference Stuff        *
\********************************/

/* Setting a preference value */
void OI::Log(char *name, bool value){
  preferences->PutBoolean(name,value);
  preferences->Save();
}
void OI::Log(char *name, int value){
  preferences->PutInt(name,value);
  preferences->Save();
}
void OI::Log(char *name, char value){
  preferences->PutInt(name,value);
  preferences->Save();
}
void OI::Log(char *name, char *value){
  preferences->PutString(name,value);
  preferences->Save();
}
void OI::Log(char *name, long value){
  preferences->PutLong(name,value);
  preferences->Save();
}
void OI::Log(char *name, double value){
  preferences->PutDouble(name,value);
  preferences->Save();
}
void OI::Log(char *name, float value){
  preferences->PutFloat(name,value);
  preferences->Save();
}

/* Getting a preference value */
void OI::Get(char *name, bool *output){
  *output = preferences->GetBoolean(name);
}
void OI::Get(char *name, int *output){
  *output = preferences->GetInt(name);
}
void OI::Get(char *name, long *output){
  *output = preferences->GetLong(name);
}
void OI::Get(char *name, char *output){
  *output = preferences->GetInt(name);
}
void OI::Get(char *name, char *output[]){
  *output = (char *)preferences->GetString(name).c_str();
}
void OI::Get(char *name, double *output){
  *output = preferences->GetDouble(name);
}
void OI::Get(char *name, float *output){
  *output = preferences->GetFloat(name);
}
