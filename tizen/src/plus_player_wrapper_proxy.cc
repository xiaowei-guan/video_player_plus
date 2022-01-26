#include "plus_player_wrapper_proxy.h"

#include <dlfcn.h>

#include "log.h"

PlusPlayerWrapperProxy::PlusPlayerWrapperProxy() {
  plus_player_hander_ = dlopen("libplus_player_wrapper.so", RTLD_LAZY);
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed %s: ", dlerror());
  }
}
PlusPlayerWrapperProxy::~PlusPlayerWrapperProxy() {
  LOG_ERROR("~PlusPlayerWrapperProxy");
  if (plus_player_hander_) {
    dlclose(plus_player_hander_);
    plus_player_hander_ = nullptr;
  }
}

PlusPlayerRef PlusPlayerWrapperProxy::CreatePlayer() {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return nullptr;
  }
  PlusPlayerRef (*CreatePlayer)();
  *(void**)(&CreatePlayer) = dlsym(plus_player_hander_, "CreatePlayer");
  if (CreatePlayer) {
    return CreatePlayer();
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return nullptr;
  }
}

bool PlusPlayerWrapperProxy::Open(PlusPlayerRef player, const char* uri) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Open)(PlusPlayerRef player, const char* uri);
  *(void**)(&Open) = dlsym(plus_player_hander_, "Open");
  if (Open) {
    return Open(player, uri);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

void PlusPlayerWrapperProxy::SetAppId(PlusPlayerRef player,
                                      const char* app_id) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetAppId)(PlusPlayerRef player, const char* app_id);
  *(void**)(&SetAppId) = dlsym(plus_player_hander_, "SetAppId");
  if (SetAppId) {
    SetAppId(player, app_id);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetPrebufferMode(PlusPlayerRef player,
                                              bool is_prebuffer_mode) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetPrebufferMode)(PlusPlayerRef player, bool is_prebuffer_mode);
  *(void**)(&SetPrebufferMode) = dlsym(plus_player_hander_, "SetPrebufferMode");
  if (SetPrebufferMode) {
    SetPrebufferMode(player, is_prebuffer_mode);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

bool PlusPlayerWrapperProxy::StopSource(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*StopSource)(PlusPlayerRef player);
  *(void**)(&StopSource) = dlsym(plus_player_hander_, "StopSource");
  if (StopSource) {
    return StopSource(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetDisplay(PlusPlayerRef player,
                                        const plusplayer::DisplayType& type,
                                        const uint32_t serface_id, const int x,
                                        const int y, const int w, const int h) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetDisplay)(PlusPlayerRef player, const plusplayer::DisplayType& type,
                     const uint32_t serface_id, const int x, const int y,
                     const int w, const int h);
  *(void**)(&SetDisplay) = dlsym(plus_player_hander_, "SetDisplay");
  if (SetDisplay) {
    return SetDisplay(player, type, serface_id, x, y, w, h);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetDisplayMode(
    PlusPlayerRef player, const plusplayer::DisplayMode& mode) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetDisplayMode)(PlusPlayerRef player,
                         const plusplayer::DisplayMode& mode);
  *(void**)(&SetDisplayMode) = dlsym(plus_player_hander_, "SetDisplayMode");
  if (SetDisplayMode) {
    return SetDisplayMode(player, mode);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetDisplayRoi(PlusPlayerRef player,
                                           const plusplayer::Geometry& roi) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetDisplayRoi)(PlusPlayerRef player, const plusplayer::Geometry& roi);
  *(void**)(&SetDisplayRoi) = dlsym(plus_player_hander_, "SetDisplayRoi");
  if (SetDisplayRoi) {
    return SetDisplayRoi(player, roi);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetDisplayRotate(
    PlusPlayerRef player, const plusplayer::DisplayRotation& rotate) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetDisplayRotate)(PlusPlayerRef player,
                           const plusplayer::DisplayRotation& rotate);
  *(void**)(&SetDisplayRotate) = dlsym(plus_player_hander_, "SetDisplayRotate");
  if (SetDisplayRotate) {
    return SetDisplayRotate(player, rotate);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::GetDisplayRotate(
    PlusPlayerRef player, plusplayer::DisplayRotation* rotate) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*GetDisplayRotate)(PlusPlayerRef player,
                           plusplayer::DisplayRotation * rotate);
  *(void**)(&GetDisplayRotate) = dlsym(plus_player_hander_, "GetDisplayRotate");
  if (GetDisplayRotate) {
    return GetDisplayRotate(player, rotate);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetDisplayVisible(PlusPlayerRef player,
                                               bool is_visible) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetDisplayVisible)(PlusPlayerRef player, bool is_visible);
  *(void**)(&SetDisplayVisible) =
      dlsym(plus_player_hander_, "SetDisplayVisible");
  if (SetDisplayVisible) {
    return SetDisplayVisible(player, is_visible);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetAudioMute(PlusPlayerRef player, bool is_mute) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetAudioMute)(PlusPlayerRef player, bool is_mute);
  *(void**)(&SetAudioMute) = dlsym(plus_player_hander_, "SetAudioMute");
  if (SetAudioMute) {
    return SetAudioMute(player, is_mute);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

plusplayer::State PlusPlayerWrapperProxy::GetState(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return plusplayer::State::kNone;
  }
  plusplayer::State (*GetState)(PlusPlayerRef player);
  *(void**)(&GetState) = dlsym(plus_player_hander_, "GetState");
  if (GetState) {
    return GetState(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return plusplayer::State::kNone;
  }
}

bool PlusPlayerWrapperProxy::GetDuration(PlusPlayerRef player,
                                         int64_t* duration_in_milliseconds) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*GetDuration)(PlusPlayerRef player, int64_t * duration_in_milliseconds);
  *(void**)(&GetDuration) = dlsym(plus_player_hander_, "GetDuration");
  if (GetDuration) {
    return GetDuration(player, duration_in_milliseconds);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::GetPlayingTime(PlusPlayerRef player,
                                            uint64_t* time_in_milliseconds) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*GetPlayingTime)(PlusPlayerRef player, uint64_t * time_in_milliseconds);
  *(void**)(&GetPlayingTime) = dlsym(plus_player_hander_, "GetPlayingTime");
  if (GetPlayingTime) {
    return GetPlayingTime(player, time_in_milliseconds);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::SetPlaybackRate(PlusPlayerRef player,
                                             const double speed) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*SetPlaybackRate)(PlusPlayerRef player, const double speed);
  *(void**)(&SetPlaybackRate) = dlsym(plus_player_hander_, "SetPlaybackRate");
  if (SetPlaybackRate) {
    return SetPlaybackRate(player, speed);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Prepare(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Prepare)(PlusPlayerRef player);
  *(void**)(&Prepare) = dlsym(plus_player_hander_, "Prepare");
  if (Prepare) {
    return Prepare(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::PrepareAsync(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*PrepareAsync)(PlusPlayerRef player);
  *(void**)(&PrepareAsync) = dlsym(plus_player_hander_, "PrepareAsync");
  if (PrepareAsync) {
    return PrepareAsync(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Start(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Start)(PlusPlayerRef player);
  *(void**)(&Start) = dlsym(plus_player_hander_, "Start");
  if (Start) {
    return Start(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Stop(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Stop)(PlusPlayerRef player);
  *(void**)(&Stop) = dlsym(plus_player_hander_, "Stop");
  if (Stop) {
    return Stop(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Pause(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Pause)(PlusPlayerRef player);
  *(void**)(&Pause) = dlsym(plus_player_hander_, "Pause");
  if (Pause) {
    return Pause(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Resume(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Resume)(PlusPlayerRef player);
  *(void**)(&Resume) = dlsym(plus_player_hander_, "Resume");
  if (Resume) {
    return Resume(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Seek(PlusPlayerRef player,
                                  const uint64_t time_millisecond) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Seek)(PlusPlayerRef player, const uint64_t time_millisecond);
  *(void**)(&Seek) = dlsym(plus_player_hander_, "Seek");
  if (Seek) {
    return Seek(player, time_millisecond);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

void PlusPlayerWrapperProxy::SetStopPosition(PlusPlayerRef player,
                                             const uint64_t time_millisecond) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*SetStopPosition)(PlusPlayerRef player,
                          const uint64_t time_millisecond);
  *(void**)(&SetStopPosition) = dlsym(plus_player_hander_, "SetStopPosition");
  if (SetStopPosition) {
    SetStopPosition(player, time_millisecond);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

bool PlusPlayerWrapperProxy::Suspend(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Suspend)(PlusPlayerRef player);
  *(void**)(&Suspend) = dlsym(plus_player_hander_, "Suspend");
  if (Suspend) {
    return Suspend(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::Restore(PlusPlayerRef player,
                                     plusplayer::State state) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Restore)(PlusPlayerRef player, plusplayer::State state);
  *(void**)(&Restore) = dlsym(plus_player_hander_, "Restore");
  if (Restore) {
    return Restore(player, state);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

bool PlusPlayerWrapperProxy::GetVideoSize(PlusPlayerRef player, int* width,
                                          int* height) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*GetVideoSize)(PlusPlayerRef player, int* width, int* height);
  *(void**)(&GetVideoSize) = dlsym(plus_player_hander_, "GetVideoSize");
  if (GetVideoSize) {
    return GetVideoSize(player, width, height);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

int PlusPlayerWrapperProxy::GetSurfaceId(PlusPlayerRef player, void* window) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return -1;
  }
  int (*GetSurfaceId)(PlusPlayerRef player, void* window);
  *(void**)(&GetSurfaceId) = dlsym(plus_player_hander_, "GetSurfaceId");
  if (GetSurfaceId) {
    return GetSurfaceId(player, window);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return -1;
  }
}

bool PlusPlayerWrapperProxy::Close(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return false;
  }
  bool (*Close)(PlusPlayerRef player);
  *(void**)(&Close) = dlsym(plus_player_hander_, "Close");
  if (Close) {
    return Close(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
    return false;
  }
}

void PlusPlayerWrapperProxy::DestroyPlayer(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*DestroyPlayer)(PlusPlayerRef player);
  *(void**)(&DestroyPlayer) = dlsym(plus_player_hander_, "DestroyPlayer");
  if (DestroyPlayer) {
    DestroyPlayer(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetCompletedCallback(PlusPlayerRef player,
                                                  OnPlayerCompleted callback,
                                                  void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetCompletedCallback)(PlusPlayerRef player, OnPlayerCompleted callback,
                               void* user_data);
  *(void**)(&SetCompletedCallback) =
      dlsym(plus_player_hander_, "SetCompletedCallback");
  if (SetCompletedCallback) {
    SetCompletedCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetCompletedCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetCompletedCallback)(PlusPlayerRef player);
  *(void**)(&UnsetCompletedCallback) =
      dlsym(plus_player_hander_, "UnsetCompletedCallback");
  if (UnsetCompletedCallback) {
    UnsetCompletedCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetBufferingCallback(PlusPlayerRef player,
                                                  OnPlayerBuffering callback,
                                                  void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetBufferingCallback)(PlusPlayerRef player, OnPlayerBuffering callback,
                               void* user_data);
  *(void**)(&SetBufferingCallback) =
      dlsym(plus_player_hander_, "SetBufferingCallback");
  if (SetBufferingCallback) {
    SetBufferingCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetBufferingCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetBufferingCallback)(PlusPlayerRef player);
  *(void**)(&UnsetBufferingCallback) =
      dlsym(plus_player_hander_, "UnsetBufferingCallback");
  if (UnsetBufferingCallback) {
    UnsetBufferingCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetPreparedCallback(PlusPlayerRef player,
                                                 OnPlayerPrepared callback,
                                                 void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetPreparedCallback)(PlusPlayerRef player, OnPlayerPrepared callback,
                              void* user_data);
  *(void**)(&SetPreparedCallback) =
      dlsym(plus_player_hander_, "SetPreparedCallback");
  if (SetPreparedCallback) {
    SetPreparedCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetPreparedCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetPreparedCallback)(PlusPlayerRef player);
  *(void**)(&UnsetPreparedCallback) =
      dlsym(plus_player_hander_, "UnsetPreparedCallback");
  if (UnsetPreparedCallback) {
    UnsetPreparedCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetResourceConflictedCallback(
    PlusPlayerRef player, OnPlayerResourceConflicted callback,
    void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetResourceConflictedCallback)(PlusPlayerRef player,
                                        OnPlayerResourceConflicted callback,
                                        void* user_data);
  *(void**)(&SetResourceConflictedCallback) =
      dlsym(plus_player_hander_, "SetResourceConflictedCallback");
  if (SetResourceConflictedCallback) {
    SetResourceConflictedCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetResourceConflictedCallback(
    PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetResourceConflictedCallback)(PlusPlayerRef player);
  *(void**)(&UnsetResourceConflictedCallback) =
      dlsym(plus_player_hander_, "UnsetResourceConflictedCallback");
  if (UnsetResourceConflictedCallback) {
    UnsetResourceConflictedCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetPlayingCallback(PlusPlayerRef player,
                                                OnPlayerPlaying callback,
                                                void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetPlayingCallback)(PlusPlayerRef player, OnPlayerPlaying callback,
                             void* user_data);
  *(void**)(&SetPlayingCallback) =
      dlsym(plus_player_hander_, "plusplayer_playing_cb");
  if (SetPlayingCallback) {
    SetPlayingCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetPlayingCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetPlayingCallback)(PlusPlayerRef player);
  *(void**)(&UnsetPlayingCallback) =
      dlsym(plus_player_hander_, "UnsetPlayingCallback");
  if (UnsetPlayingCallback) {
    UnsetPlayingCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetErrorCallback(PlusPlayerRef player,
                                              OnPlayerError callback,
                                              void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetErrorCallback)(PlusPlayerRef player, OnPlayerError callback,
                           void* user_data);
  *(void**)(&SetErrorCallback) = dlsym(plus_player_hander_, "SetErrorCallback");
  if (SetErrorCallback) {
    SetErrorCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetErrorCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetErrorCallback)(PlusPlayerRef player);
  *(void**)(&UnsetErrorCallback) =
      dlsym(plus_player_hander_, "UnsetErrorCallback");
  if (UnsetErrorCallback) {
    UnsetErrorCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetErrorMessageCallback(
    PlusPlayerRef player, OnPlayerErrorMessage callback, void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*SetErrorMessageCallback)(PlusPlayerRef player);
  *(void**)(&SetErrorMessageCallback) =
      dlsym(plus_player_hander_, "SetErrorMessageCallback");
  if (SetErrorMessageCallback) {
    SetErrorMessageCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetErrorMessageCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetErrorMessageCallback)(PlusPlayerRef player);
  *(void**)(&UnsetErrorMessageCallback) =
      dlsym(plus_player_hander_, "UnsetErrorMessageCallback");
  if (UnsetErrorMessageCallback) {
    UnsetErrorMessageCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetSeekCompletedCallback(
    PlusPlayerRef player, OnPlayerSeekCompleted callback, void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*SetSeekCompletedCallback)(
      PlusPlayerRef player, OnPlayerSeekCompleted callback, void* user_data);
  *(void**)(&SetSeekCompletedCallback) =
      dlsym(plus_player_hander_, "SetSeekCompletedCallback");
  if (SetSeekCompletedCallback) {
    SetSeekCompletedCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetSeekCompletedCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetSeekCompletedCallback)(PlusPlayerRef player);
  *(void**)(&UnsetSeekCompletedCallback) =
      dlsym(plus_player_hander_, "UnsetSeekCompletedCallback");
  if (UnsetSeekCompletedCallback) {
    UnsetSeekCompletedCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetAdaptiveStreamingControlCallback(
    PlusPlayerRef player, OnPlayerAdaptiveStreamingControl callback,
    void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*SetAdaptiveStreamingControlCallback)(
      PlusPlayerRef player, OnPlayerAdaptiveStreamingControl callback,
      void* user_data);
  *(void**)(&SetAdaptiveStreamingControlCallback) =
      dlsym(plus_player_hander_, "SetAdaptiveStreamingControlCallback");
  if (SetAdaptiveStreamingControlCallback) {
    SetAdaptiveStreamingControlCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetAdaptiveStreamingControlCallback(
    PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  bool (*UnsetAdaptiveStreamingControlCallback)(PlusPlayerRef player);
  *(void**)(&UnsetAdaptiveStreamingControlCallback) =
      dlsym(plus_player_hander_, "UnsetAdaptiveStreamingControlCallback");
  if (UnsetAdaptiveStreamingControlCallback) {
    UnsetAdaptiveStreamingControlCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetDrm(PlusPlayerRef player,
                                    const plusplayer::drm::Property& property) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetDrm)(PlusPlayerRef player,
                 const plusplayer::drm::Property& property);
  *(void**)(&SetDrm) = dlsym(plus_player_hander_, "SetDrm");
  if (SetDrm) {
    SetDrm(player, property);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::DrmLicenseAcquiredDone(
    PlusPlayerRef player, plusplayer::TrackType type) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*DrmLicenseAcquiredDone)(PlusPlayerRef player,
                                 plusplayer::TrackType type);
  *(void**)(&DrmLicenseAcquiredDone) =
      dlsym(plus_player_hander_, "DrmLicenseAcquiredDone");
  if (DrmLicenseAcquiredDone) {
    DrmLicenseAcquiredDone(player, type);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::SetDrmInitDataCallback(
    PlusPlayerRef player, OnPlayerDrmInitData callback, void* user_data) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*SetDrmInitDataCallback)(PlusPlayerRef player,
                                 OnPlayerDrmInitData callback, void* user_data);
  *(void**)(&SetDrmInitDataCallback) =
      dlsym(plus_player_hander_, "SetDrmInitDataCallback");
  if (SetDrmInitDataCallback) {
    SetDrmInitDataCallback(player, callback, user_data);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}

void PlusPlayerWrapperProxy::UnsetDrmInitDataCallback(PlusPlayerRef player) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return;
  }
  void (*UnsetDrmInitDataCallback)(PlusPlayerRef player);
  *(void**)(&UnsetDrmInitDataCallback) =
      dlsym(plus_player_hander_, "UnsetDrmInitDataCallback");
  if (UnsetDrmInitDataCallback) {
    UnsetDrmInitDataCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}
