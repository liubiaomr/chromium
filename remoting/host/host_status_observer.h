// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_HOST_STATUS_OBSERVER_H_
#define REMOTING_HOST_HOST_STATUS_OBSERVER_H_

#include <string>

namespace remoting {
class SignalStrategy;

// Interface for host status observer. All methods are invoked on the
// network thread.
class HostStatusObserver {
 public:
  HostStatusObserver() { }
  virtual ~HostStatusObserver() { }

  // Called when status of the signalling channel changes.
  virtual void OnSignallingConnected(SignalStrategy* signal_strategy) = 0;
  virtual void OnSignallingDisconnected() = 0;

  // Called when an unauthorized user attempts to connect to the host.
  virtual void OnAccessDenied() = 0;

  // Called when a client authenticates, or disconnects. Observers
  // must not tear-down ChromotingHost state on receipt of this
  // callback; it is purely informational.
  virtual void OnClientAuthenticated(const std::string& jid) = 0;
  virtual void OnClientDisconnected(const std::string& jid) = 0;

  // Called when the host shuts down.
  virtual void OnShutdown() = 0;
};

}  // namespace remoting

#endif  // REMOTING_HOST_HOST_STATUS_OBSERVER_H_
