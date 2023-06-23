// FlatOut 2 Decompilation

#include <stdio.h>
#include <stdarg.h>
#include <memoryapi.h>
#include <WinUser.h>
#include <d3d9.h>
#include <wingdi.h>
#include <strsafe.h>
#include <winreg.h>
#include <timeapi.h>
#include <combaseapi.h>

// Structs

struct undefined4{
    float nothing;
};


// Settings Structures
// Got this info from the cfg files

struct Version{
  int Settings = 15; // 0 - 1,000,000
};

struct Game{
  bool ImperialUnits = false;
  bool OverlayGauges = true;
  bool IngameMap = true;
  bool Ragdoll = true;
  bool ShowBonus = true;
  bool ShowTutorials = true;
  char DefaultPlayerName[30] = "PLAYER"; // idk, 30 chars max sounds good.
  int Camera = 0; // 0 - 9
  int Hud = 0;    // 0 - 4
};

struct Control{
  char ControllerGuid[33] = "00000000000000000000000000000000";
  int Controller = 0;                     // 0 - 2
  int ForceMagnitude = 100;               // 0 - 100
  int ControllerSensitivity = 90;         // 0 - 100
  int ControllerDeadzone = 0;             // 0 - 100
  int ControllerSaturation = 90;          // 0 - 100
  int ControllerLayout = 0;               // 0 - 10
  bool ForceFeedback = true;
  float DigitalCenteringSpeed = 0.999f;   // 0.0 - 100.0
  float DigitalSteeringMaxSpeed = 1.85f;  // 0.0 - 100.0
  float DigitalSteeringMinSpeed = 1.25f;  // 0.0 - 100.0
};

struct Visual{
  bool AlphaBlend = true;
  bool SunFlare = true;
  int TextureQuality = 4;       // 0 - 4
  int TrackDetail = 2;          // 0 - 2
  int PS2MotionBlurIngame = 32; // 0 - 255
  int Visibility = 100;         // 0 - 100
};

struct Audio{
  int InterfaceMusicVolume = 50;  // 0 - 100
  int InterfaceSfxVolume = 80;    // 0 - 100
  int IngameMusicVolume = 50;     // 0 - 100
  int IngameSfxVolume =  80;      // 0 - 100
  int ChannelMode = 0;            // 0 - 2
  bool DopplerEffects = false;
};

struct Network{
  int Port = 23756;                     // 0 - 65536
  int BroadcastPort = 23757;            // 0 - 65536
  int VoiceOutputVolume = 80;           // 0 - 100
  int VoiceJitterMaxDelay = 10;         // 0 - 100
  int VoiceJitterMaxVariation = 10;     // 0 - 100
  int VoiceJitterInitialVariation = 2;  // 0 - 100
  float VoiceTalkingLevel = 15.f;       // 0.0 - 90.0
  bool MutePlayerVoice = true;
  bool MuteVoiceIngame = false;
};

struct Settings{
  struct Version Version;
  struct Game Game;
  struct Control Control;
  struct Visual Visual;
  struct Audio Audio;
  struct Network Network;
};

struct Settings Settings;


HINSTANCE g_Instance;

DLGPROC g_dlgproc;

int setupFlag = 0;


int CheckDirectXVersion(LPBYTE *expectedVersion)
{
  HKEY hkey;
  LPBYTE lpdata;
  LPDWORD lpcbdata;

  LSTATUS oStatus = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\DirectX", 0, 1, &hkey);

  if (oStatus < 0)
    return oStatus & 0xffffff00;

  LSTATUS qStatus = RegQueryValueExA(hkey, "Version", NULL, NULL, lpdata, lpcbdata);
  LSTATUS cStatus = RegCloseKey(hkey);

  if (qStatus < 0 || lpcbdata > (LPDWORD)0x20)
    return cStatus & 0xffffff00;
  

  LPBYTE *dataptr =  &lpdata;
  LPBYTE currentData;
  bool isOlder;

  while (true)
  {
    currentData = *dataptr;
    isOlder = currentData < *expectedVersion;
    // 
    if (currentData != *expectedVersion) 
      break;

    if (currentData == 0)
      return 1;
    
    currentData = dataptr[1];
    isOlder = currentData < expectedVersion[1];
    if (currentData != expectedVersion[1])
      break;

    dataptr = dataptr + 2;
    expectedVersion = expectedVersion + 2;

    if (currentData == 0)
      return 1;
  }

  return isOlder ? -1 : 1;
}

unsigned int UINT_008da72c;

unsigned int UINT_008da700;

void * MemoryPointer;
size_t size_t_008da724;


void LoadBinaryDatabase()
{
  UINT_008da700 = 0;
  free(MemoryPointer);
  MemoryPointer = NULL;
  size_t_008da724 = 0;

  //...

  CreateErrorMessageAndDie("Failed to load binary database \'%s\'!");
  return;
}

unsigned int UINT_008d7bb0;
unsigned int UINT_0069c2d0;
unsigned int UINT_008d780c;

DWORD Startup(HINSTANCE hInstance, undefined4 param_3, char *flags)
{
  g_Instance = hInstance;

  // The random seed is set to the current time
  DWORD seed = timeGetTime();
  srand(seed);

  // Dealing with the setup flag
  setupFlag = 0;
  if (flags != "" && (stricmp(flags, "-setup") || stricmp(flags, "setup")))
  {
      setupFlag = 1;
  }

  CoInitializeEx(NULL, 0);

  int verCheck = CheckDirectXVersion((LPBYTE *)"4.09.00.0904");
  if (verCheck == 0 && DialogBoxParamA(hInstance, (LPCSTR)0x83, (HWND)0x0, g_dlgproc, (LPARAM)0) == (INT_PTR)1)
    return 0xffffffff;

  // Unused flags
  strstr(flags, "-binarydb");
  strstr(flags, "-bedit");

  LoadBinaryDatabase();

  //...
}

void CreateErrorMessageAndDie(char *message)
{
  char *local_800;
  char *body [1024];
  
  sprintf(*body, "%s", &message);
  MessageBoxA(NULL, (LPCSTR)body, "Fatal error", MB_ICONERROR);
  ExitProcess(0);
}

