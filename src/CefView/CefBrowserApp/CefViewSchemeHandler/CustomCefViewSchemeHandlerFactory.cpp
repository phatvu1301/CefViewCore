#include "CustomCefViewSchemeHandlerFactory.h"

#include <CefViewBrowserClient.h>
#include <CefViewBrowserClientDelegate.h>

#include "CustomCefViewSchemeHandler.h"

CustomCefViewSchemeHandlerFactory::CustomCefViewSchemeHandlerFactory(CefRefPtr<CefViewBrowserApp> app)
  : app_(app)
{
}

CustomCefViewSchemeHandlerFactory::~CustomCefViewSchemeHandlerFactory() {}

CefRefPtr<CefResourceHandler>
CustomCefViewSchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    const CefString& scheme_name,
                                    CefRefPtr<CefRequest> request)
{
  if (!app_) {
    return nullptr;
  }

  auto client = browser->GetHost()->GetClient();
  if (!client) {
    return nullptr;
  }

  auto handler = app_->GetClientHandler(client.get());
  if (!handler) {
    return nullptr;
  }
  return new CustomCefViewSchemeHandler(browser, frame, handler);
}
