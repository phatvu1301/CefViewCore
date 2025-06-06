#ifndef CefViewCoreAssetBridge_h
#define CefViewCoreAssetBridge_h

#pragma once
typedef const char* (*FnAsset)(const char*, int*, const char**);

#ifdef __cplusplus
extern "C"{
#endif
  void SetAssetFunc(FnAsset func);
  extern FnAsset g_asset_func;
#ifdef __cplusplus
}
#endif
