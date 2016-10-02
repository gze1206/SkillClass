#pragma once
#if DEBUG
const bool STATE_IS_WINDOW = true;
#else
const bool STATE_IS_WINDOW = false;
#endif

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 1080;