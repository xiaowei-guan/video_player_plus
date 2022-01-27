#include "plus_player_wrapper_proxy.h"

#include <dlfcn.h>

#include "log.h"

typedef PlusPlayerRef (*PlusplayerCreatePlayer)();
typedef bool (*PlusplayerOpen)(PlusPlayerRef player, const char* uri);
typedef void (*PlusplayerSetAppId)(PlusPlayerRef player, const char* app_id);
typedef void (*PlusplayerSetPrebufferMode)(PlusPlayerRef player,
                                           bool is_prebuffer_mode);
typedef bool (*PlusplayerStopSource)(PlusPlayerRef player);
typedef bool (*PlusplayerSetDisplay)(PlusPlayerRef player,
                                     const plusplayer::DisplayType& type,
                                     const uint32_t serface_id, const int x,
                                     const int y, const int w, const int h);
typedef bool (*PlusplayerSetDisplayMode)(PlusPlayerRef player,
                                         const plusplayer::DisplayMode& mode);
typedef bool (*PlusplayerSetDisplayRoi)(PlusPlayerRef player,
                                        const plusplayer::Geometry& roi);
typedef bool (*PlusplayerSetDisplayRotate)(
    PlusPlayerRef player, const plusplayer::DisplayRotation& rotate);
typedef bool (*PlusplayGetDisplayRotate)(PlusPlayerRef player,
                                         plusplayer::DisplayRotation* rotate);
typedef bool (*PlusplaySetDisplayVisible)(PlusPlayerRef player,
                                          bool is_visible);
typedef bool (*PlusplaySetAudioMute)(PlusPlayerRef player, bool is_mute);
typedef plusplayer::State (*PlusplayGetState)(PlusPlayerRef player);
typedef bool (*PlusplayGetDuration)(PlusPlayerRef player,
                                    int64_t* duration_in_milliseconds);
typedef bool (*PlusplayGetPlayingTime)(PlusPlayerRef player,
                                       uint64_t* time_in_milliseconds);

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

void* PlusPlayerWrapperProxy::Dlsym(const char* name) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return nullptr;
  }
  return dlsym(plus_player_hander_, name);
}

PlusPlayerRef PlusPlayerWrapperProxy::CreatePlayer() {
  PlusplayerCreatePlayer method_create_player;
  *(void**)(&method_create_player) = Dlsym("CreatePlayer");
  if (method_create_player) {
    return method_create_player();
  }
  return nullptr;
}

bool PlusPlayerWrapperProxy::Open(PlusPlayerRef player, const char* uri) {
  PlusplayerOpen method_open;
  *(void**)(&method_open) = Dlsym("Open");
  if (method_open) {
    return method_open(player, uri);
  }
  return false;
}

void PlusPlayerWrapperProxy::SetAppId(PlusPlayerRef player,
                                      const char* app_id) {
  PlusplayerSetAppId method_set_app_id;
  *(void**)(&method_set_app_id) = Dlsym("SetAppId");
  if (method_set_app_id) {
    method_set_app_id(player, app_id);
  }
}

void PlusPlayerWrapperProxy::SetPrebufferMode(PlusPlayerRef player,
                                              bool is_prebuffer_mode) {
  PlusplayerSetPrebufferMode method_set_prebuffer_mode;
  *(void**)(&method_set_prebuffer_mode) = Dlsym("SetPrebufferMode");
  if (method_set_prebuffer_mode) {
    method_set_prebuffer_mode(player, is_prebuffer_mode);
  }
}

bool PlusPlayerWrapperProxy::StopSource(PlusPlayerRef player) {
  PlusplayerStopSource method_stop_source;
  *(void**)(&method_stop_source) = Dlsym("StopSource");
  if (method_stop_source) {
    return method_stop_source(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetDisplay(PlusPlayerRef player,
                                        const plusplayer::DisplayType& type,
                                        const uint32_t serface_id, const int x,
                                        const int y, const int w, const int h) {
  PlusplayerSetDisplay method_set_display;
  *(void**)(&method_set_display) = Dlsym("SetDisplay");
  if (method_set_display) {
    return method_set_display(player, type, serface_id, x, y, w, h);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetDisplayMode(
    PlusPlayerRef player, const plusplayer::DisplayMode& mode) {
  PlusplayerSetDisplayMode method_set_display_mode;
  *(void**)(&method_set_display_mode) = Dlsym("SetDisplayMode");
  if (method_set_display_mode) {
    return method_set_display_mode(player, mode);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetDisplayRoi(PlusPlayerRef player,
                                           const plusplayer::Geometry& roi) {
  PlusplayerSetDisplayRoi method_set_display_roi;
  *(void**)(&method_set_display_roi) = Dlsym("SetDisplayRoi");
  if (method_set_display_roi) {
    return method_set_display_roi(player, roi);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetDisplayRotate(
    PlusPlayerRef player, const plusplayer::DisplayRotation& rotate) {
  PlusplayerSetDisplayRotate method_set_display_rotate;
  *(void**)(&method_set_display_rotate) = Dlsym("SetDisplayRotate");
  if (method_set_display_rotate) {
    return method_set_display_rotate(player, rotate);
  }
  return false;
}

bool PlusPlayerWrapperProxy::GetDisplayRotate(
    PlusPlayerRef player, plusplayer::DisplayRotation* rotate) {
  PlusplayGetDisplayRotate method_get_display_rotate;
  *(void**)(&method_get_display_rotate) = Dlsym("GetDisplayRotate");
  if (method_get_display_rotate) {
    return method_get_display_rotate(player, rotate);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetDisplayVisible(PlusPlayerRef player,
                                               bool is_visible) {
  PlusplaySetDisplayVisible method_set_display_visible;
  *(void**)(&method_set_display_visible) = Dlsym("SetDisplayVisible");
  if (method_set_display_visible) {
    return method_set_display_visible(player, is_visible);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetAudioMute(PlusPlayerRef player, bool is_mute) {
  PlusplaySetAudioMute method_set_audio_mute;
  *(void**)(&method_set_audio_mute) = Dlsym("SetAudioMute");
  if (method_set_audio_mute) {
    return method_set_audio_mute(player, is_mute);
  }
  return false;
}

plusplayer::State PlusPlayerWrapperProxy::GetState(PlusPlayerRef player) {
  PlusplayGetState method_get_state;
  *(void**)(&method_get_state) = Dlsym("GetState");
  if (method_get_state) {
    return method_get_state(player);
  }
  return plusplayer::State::kNone;
}

bool PlusPlayerWrapperProxy::GetDuration(PlusPlayerRef player,
                                         int64_t* duration_in_milliseconds) {
  PlusplayGetDuration method_get_duration;
  *(void**)(&method_get_duration) = Dlsym("GetDuration");
  if (method_get_duration) {
    return method_get_duration(player, duration_in_milliseconds);
  }
  return false;
}

bool PlusPlayerWrapperProxy::GetPlayingTime(PlusPlayerRef player,
                                            uint64_t* time_in_milliseconds) {
  PlusplayGetPlayingTime method_get_playing_time;
  *(void**)(&method_get_playing_time) = Dlsym("GetPlayingTime");
  if (method_get_playing_time) {
    return method_get_playing_time(player, time_in_milliseconds);
  }
  return false;
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
  void (*UnsetDrmInitDataCallback)(PlusPlayerRef player);
  *(void**)(&UnsetDrmInitDataCallback) =
      dlsym(plus_player_hander_, "UnsetDrmInitDataCallback");
  if (UnsetDrmInitDataCallback) {
    UnsetDrmInitDataCallback(player);
  } else {
    LOG_ERROR("Symbol not found %s: ", dlerror());
  }
}
