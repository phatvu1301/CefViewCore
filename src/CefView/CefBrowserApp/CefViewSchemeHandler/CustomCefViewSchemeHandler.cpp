#include "CustomCefViewSchemeHandler.h"
#include "CefViewCoreAssetBridge.h"
#include <cstring>
#include <iostream>

CustomCefViewSchemeHandler::CustomCefViewSchemeHandler(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefFrame> frame,
                                           CefViewBrowserClientDelegateInterface::RefPtr delegate)
  : browser_(browser)
  , frame_(frame)
  , handler_delegate_(delegate)
  , offset_(0)
{
}

CustomCefViewSchemeHandler::~CustomCefViewSchemeHandler() {}

bool
CustomCefViewSchemeHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback)
{
  // DCHECK(!CefCurrentlyOn(TID_UI) && !CefCurrentlyOn(TID_IO));

  handle_request = true;

  auto browserDelegate = handler_delegate_.lock();
  if (browserDelegate) {
    CefString cefStrUrl = request->GetURL();
    browserDelegate->processUrlRequest(browser_, frame_, cefStrUrl.ToString());
    std::cout << "Using Custom Scheme - Open -1 " <<  cefStrUrl << std::endl;
  }

  std::string url = request->GetURL();
  std::string path;
  std::cout << "Using Custom Scheme - Open -2 " <<  url << std::endl;


  size_t pos = url.find("://");
  if (pos != std::string::npos) {
    path = url.substr(pos + 3);
  } else {
    path = url;
  }
  while (!path.empty() && path.back() == '/') path.pop_back();

  // size_t schemePos = url.find("://");
  // std::string afterScheme = url.substr(schemePos + 3);
  //
  // auto slash = afterScheme.find('/');
  // if (slash != std::string::npos)
  //   afterScheme = afterScheme.substr(slash + 1);
  //
  // while (!afterScheme.empty() && afterScheme.back() == '/')
  //   afterScheme.pop_back();
  // if (afterScheme.empty()) afterScheme = "index.html";
  //
  // path = afterScheme;

  std::cout << "Using Custom Scheme - Open - Path  " <<  path << std::endl;


  data_.clear();
  mime_type_ = "application/octet-stream";

  int len = 0;
  const char* cmime = nullptr;

  if (g_asset_func) {
    std::cout << "Using Custom Scheme - g_asset_func 1 " <<  g_asset_func << std::endl;
    const char* buf = g_asset_func(path.c_str(), &len, &cmime);
    if (buf && len > 0) {
      data_.assign(buf, len);
      if (cmime) {
        mime_type_ = cmime;
        g_free_func(const_cast<char*>(cmime));
      } else {
        mime_type_ = "application/octet-stream";
      }
      std::cout << "Using Custom Scheme - g_asset_func 2 " << buf << std::endl;
      g_free_func(const_cast<char*>(buf));
    } else {
      data_ = "404 - Not Found";
      mime_type_ = "text/plain";
    }
  } else {
    data_ = "Asset bridge not set";
    mime_type_ = "text/plain";
  }
  std::cout << "[CEF SCHEME] path=" << path << ", len=" << len << ", mime=" << mime_type_ << std::endl;
  return true;
}

void
CustomCefViewSchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
                                         int64_t& response_length,
                                         CefString& redirectUrl)
{
  CEF_REQUIRE_IO_THREAD();

  DCHECK(!data_.empty());
  response->SetMimeType(mime_type_);
  response->SetStatus(200);
  // Set the resulting response length
  response_length = data_.length();
  response->SetHeaderByName("Access-Control-Allow-Origin", "*", true);
}

bool
CustomCefViewSchemeHandler::Skip(int64_t bytes_to_skip, int64_t& bytes_skipped, CefRefPtr<CefResourceSkipCallback> callback)
{
  // CEF_REQUIRE_IO_THREAD();

  bytes_skipped = 0;

  offset_ += bytes_to_skip;
  if (offset_ <= (int)data_.length()) {
    bytes_skipped = bytes_to_skip;
  } else {
    offset_ = (int)data_.length();
    bytes_skipped = data_.length() - offset_;
  }

  return true;
}

bool
CustomCefViewSchemeHandler::Read(void* data_out,
                           int bytes_to_read,
                           int& bytes_read,
                           CefRefPtr<CefResourceReadCallback> callback)
{
  // DCHECK(!CefCurrentlyOn(TID_UI) && !CefCurrentlyOn(TID_IO));

  bytes_read = 0;
  if (offset_ < (int)data_.length()) {
    // Copy the next block of data into the buffer.
    int transfer_size = std::min(bytes_to_read, static_cast<int>(data_.length() - offset_));
    memcpy(data_out, data_.c_str() + offset_, transfer_size);
    offset_ += transfer_size;
    bytes_read = transfer_size;
  }

  return bytes_read > 0;
}

void
CustomCefViewSchemeHandler::Cancel()
{
}
