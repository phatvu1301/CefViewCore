#ifndef CefViewCoreAssetBridge_h
#define CefViewCoreAssetBridge_h

#pragma once
typedef const char* (*FnAsset)(const char*, int*, const char**);
typedef void (*FnFree)(const char*);

#ifdef __cplusplus
extern "C"{
#endif
  void SetAssetFunc(FnAsset func);
  void SetFreeFunc(FnFree func);
  extern FnAsset g_asset_func;
  extern FnFree g_free_func;

#ifdef __cplusplus
}
#endif
#endif
