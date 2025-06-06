#include "CustomCefViewSchemeHandlerFactory.h"

#include <CefViewBrowserClient.h>
#include <CefViewBrowserClientDelegate.h>

#include "CustomCefViewSchemeHandler.h"

#include <iostream>

CustomCefViewSchemeHandlerFactory::CustomCefViewSchemeHandlerFactory(CefRefPtr<CefViewBrowserApp> app)
  : app_(app)
{
  std::cout << "CustomCefViewSchemeHandlerFactory - CustomCefViewSchemeHandlerFactory -1 " << std::endl;
}

CustomCefViewSchemeHandlerFactory::~CustomCefViewSchemeHandlerFactory() {}

CefRefPtr<CefResourceHandler>
CustomCefViewSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    const CefString& scheme_name,
                                    CefRefPtr<CefRequest> request)
{
  std::cout << "CustomCefViewSchemeHandlerFactory - Create -1 " << std::endl;
  if (!app_) {
    return nullptr;
  }

  auto client = browser->GetHost()->GetClient();
  if (!client) {
    std::cout << "CustomCefViewSchemeHandlerFactory - Create -2 " << std::endl;
    return nullptr;
  }

  auto handler = app_->GetClientHandler(client.get());
  if (!handler) {
    std::cout << "CustomCefViewSchemeHandlerFactory - Create -2 " << std::endl;
    return nullptr;
  }
  return new CustomCefViewSchemeHandler(browser, frame, handler);
}
