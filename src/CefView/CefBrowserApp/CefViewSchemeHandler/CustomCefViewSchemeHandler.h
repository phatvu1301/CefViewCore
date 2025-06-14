﻿
#ifndef CefViewSchemeHandler_h
#define CefViewSchemeHandler_h

#pragma once

#include <string>

#include <CefViewCoreGlobal.h>
#include <CefViewBrowserClientDelegate.h>

class CustomCefViewSchemeHandler : public CefResourceHandler
{
  IMPLEMENT_REFCOUNTING(CustomCefViewSchemeHandler);

private:
  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefBrowser> browser_;

  /// <summary>
  ///
  /// </summary>
  CefRefPtr<CefFrame> frame_;

  /// <summary>
  ///
  /// </summary>
  CefViewBrowserClientDelegateInterface::WeakPtr handler_delegate_;

  int offset_;
  std::string data_;
  std::string mime_type_;

public:
  CustomCefViewSchemeHandler(CefRefPtr<CefBrowser> browser,
                       CefRefPtr<CefFrame> frame,
                       CefViewBrowserClientDelegateInterface::RefPtr delegate);

  ~CustomCefViewSchemeHandler();

  virtual bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;

  virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
                                  int64_t& response_length,
                                  CefString& redirectUrl) override;

  virtual bool Skip(int64_t bytes_to_skip,
                    int64_t& bytes_skipped,
                    CefRefPtr<CefResourceSkipCallback> callback) override;

  virtual bool Read(void* data_out,
                    int bytes_to_read,
                    int& bytes_read,
                    CefRefPtr<CefResourceReadCallback> callback) override;

  virtual void Cancel() override;
};

#endif
