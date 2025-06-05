

#ifndef CustomCefViewSchemeHandlerFactory_h
#define CustomCefViewSchemeHandlerFactory_h

#pragma once

#include <CefViewCoreGlobal.h>
#include <CefViewBrowserApp.h>

class CustomCefViewSchemeHandlerFactory : public CefSchemeHandlerFactory
{
  IMPLEMENT_REFCOUNTING(CustomCefViewSchemeHandlerFactory);

private:
  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefViewBrowserApp> app_;

public:
  /// <summary>
  ///
  /// </summary>
  /// <param name="delegate"></param>
  CustomCefViewSchemeHandlerFactory(CefRefPtr<CefViewBrowserApp> app);

  /// <summary>
  ///
  /// </summary>
  ~CustomCefViewSchemeHandlerFactory();

  /// <summary>
  ///
  /// </summary>
  /// <param name="browser"></param>
  /// <param name="frame"></param>
  /// <param name="scheme_name"></param>
  /// <param name="request"></param>
  /// <returns></returns>
  virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                               CefRefPtr<CefFrame> frame,
                                               const CefString& scheme_name,
                                               CefRefPtr<CefRequest> request) override;
};

#endif
