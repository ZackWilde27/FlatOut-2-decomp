#pragma once

// Lua 5.1
// I don't know the exact version that was used, but 5.1.5 can be downloaded from here.
// https://www.lua.org/versions.html#5.1
// It's from 2012 but it's the only version of 5.1 available.
// According to 5.1.5's code there should be a full version string somewhere but there isn't one, does that mean they used 5.1.0?
extern "C" {
#include "Engine/lua-5.1.5/src/lapi.h"
#include "Engine/lua-5.1.5/src/lauxlib.h"
#include "Engine/lua-5.1.5/src/lcode.h"
#include "Engine/lua-5.1.5/src/ldebug.h"
#include "Engine/lua-5.1.5/src/ldo.h"
#include "Engine/lua-5.1.5/src/lfunc.h"
#include "Engine/lua-5.1.5/src/lgc.h"
#include "Engine/lua-5.1.5/src/llex.h"
#include "Engine/lua-5.1.5/src/llimits.h"
}