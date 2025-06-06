
#include "CefViewCoreAssetBridge.h"

static FnAsset g_asset_func = nullptr;

void
SetAssetFunc(FnAsset func)
{
  g_asset_func = func;
}
