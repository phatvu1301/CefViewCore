#include "CustomCefViewSchemeHandlerFactory.h"

#include <CefViewBrowserClient.h>
#include <CefViewBrowserClientDelegate.h>

#include "CustomCefViewSchemeHandler.h"

#include <iostream>

CustomCefViewSchemeHandlerFactory::CustomCefViewSchemeHandlerFactory(CefRefPtr<CefViewBrowserApp> app)
  : app_(app)
{
  std::cout << "CustomCefViewSchemeHandlerFactory - 1 " << std::endl;
}

CustomCefViewSchemeHandlerFactory::~CustomCefViewSchemeHandlerFactory() {}

CefRefPtr<CefResourceHandler>
CustomCefViewSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    const CefString& scheme_name,
                                    CefRefPtr<CefRequest> request)
{
  std::cout << "CustomCefViewSchemeHandlerFactory - START " << std::endl;
  std::cout << "CustomCefViewSchemeHandlerFactory - START scheme_name " << scheme_name <<std::endl;
  std::cout << "CustomCefViewSchemeHandlerFactory - START request" << request->GetURL() <<std::endl;
  std::cout << "CustomCefViewSchemeHandlerFactory - START frame" << frame->GetIdentifier() <<std::endl;


  if (!app_) {
    return nullptr;
  }

  auto client = browser->GetHost()->GetClient();
  if (!client) {
    std::cout << "CustomCefViewSchemeHandlerFactory - Fail - 1 " << std::endl;
    return nullptr;
  }

  auto handler = app_->GetClientHandler(client.get());
  if (!handler) {
    std::cout << "CustomCefViewSchemeHandlerFactory - Fail - 2 " << std::endl;
    return nullptr;
  }
  std::cout << "CustomCefViewSchemeHandlerFactory - END " << std::endl;
  return new CustomCefViewSchemeHandler(browser, frame, handler);
}
