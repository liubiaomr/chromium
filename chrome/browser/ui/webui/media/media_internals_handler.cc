// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/webui/media/media_internals_handler.h"

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/values.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/ui/webui/media/media_internals_proxy.h"
#include "content/browser/renderer_host/render_view_host.h"
#include "content/browser/webui/web_ui.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/web_contents.h"

using content::BrowserThread;

MediaInternalsMessageHandler::MediaInternalsMessageHandler()
    : proxy_(new MediaInternalsProxy()) {}

MediaInternalsMessageHandler::~MediaInternalsMessageHandler() {
  proxy_->Detach();
}

void MediaInternalsMessageHandler::RegisterMessages() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  proxy_->Attach(this);

  web_ui()->RegisterMessageCallback("getEverything",
      base::Bind(&MediaInternalsMessageHandler::OnGetEverything,
                 base::Unretained(this)));
}

void MediaInternalsMessageHandler::OnGetEverything(const ListValue* list) {
  proxy_->GetEverything();
}

void MediaInternalsMessageHandler::OnUpdate(const string16& update) {
  // Don't try to execute JavaScript in a RenderView that no longer exists.
  RenderViewHost* host = web_ui()->web_contents()->GetRenderViewHost();
  if (host)
    host->ExecuteJavascriptInWebFrame(string16(), update);
}
