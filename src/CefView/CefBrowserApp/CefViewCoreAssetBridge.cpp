
#include "CefViewCoreAssetBridge.h"

FnAsset g_asset_func = nullptr;
FnFree g_free_func = nullptr;

void
SetAssetFunc(FnAsset func)
{
  g_asset_func = func;
}

void
SetFreeFunc(FnFree func)
{
  g_free_func = func;
}
