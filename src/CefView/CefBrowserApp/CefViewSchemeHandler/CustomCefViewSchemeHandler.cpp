#include "CustomCefViewSchemeHandler.h"

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
  }

  data_ = "ok";
  mime_type_ = "text/html";

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
  // CEF_REQUIRE_IO_THREAD();
}
