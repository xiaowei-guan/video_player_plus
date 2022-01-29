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
typedef bool (*PlusplayerGetDisplayRotate)(PlusPlayerRef player,
                                           plusplayer::DisplayRotation* rotate);
typedef bool (*PlusplayerSetDisplayVisible)(PlusPlayerRef player,
                                            bool is_visible);
typedef bool (*PlusplayerSetAudioMute)(PlusPlayerRef player, bool is_mute);
typedef plusplayer::State (*PlusplayerGetState)(PlusPlayerRef player);
typedef bool (*PlusplayerGetDuration)(PlusPlayerRef player,
                                      int64_t* duration_in_milliseconds);
typedef bool (*PlusplayerGetPlayingTime)(PlusPlayerRef player,
                                         uint64_t* time_in_milliseconds);
typedef bool (*PlusplayerSetPlaybackRate)(PlusPlayerRef player,
                                          const double speed);
typedef bool (*PlusplayerPrepare)(PlusPlayerRef player);
typedef bool (*PlusplayerPrepareAsync)(PlusPlayerRef player);
typedef bool (*PlusplayerStart)(PlusPlayerRef player);
typedef bool (*PlusplayerStop)(PlusPlayerRef player);
typedef bool (*PlusplayerPause)(PlusPlayerRef player);
typedef bool (*PlusplayerResume)(PlusPlayerRef player);
typedef bool (*PlusplayerSeek)(PlusPlayerRef player,
                               const uint64_t time_millisecond);
typedef bool (*PlusplayerSetStopPosition)(PlusPlayerRef player,
                                          const uint64_t time_millisecond);
typedef bool (*PlusplayerSuspend)(PlusPlayerRef player);
typedef bool (*PlusplayerRestore)(PlusPlayerRef player,
                                  plusplayer::State state);
typedef bool (*PlusplayerGetVideoSize)(PlusPlayerRef player, int* width,
                                       int* height);
typedef int (*PlusplayerGetSurfaceId)(PlusPlayerRef player, void* window);
typedef bool (*PlusplayerClose)(PlusPlayerRef player);
typedef void (*PlusplayerDestroyPlayer)(PlusPlayerRef player);

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
  PlusplayerGetDisplayRotate method_get_display_rotate;
  *(void**)(&method_get_display_rotate) = Dlsym("GetDisplayRotate");
  if (method_get_display_rotate) {
    return method_get_display_rotate(player, rotate);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetDisplayVisible(PlusPlayerRef player,
                                               bool is_visible) {
  PlusplayerSetDisplayVisible method_set_display_visible;
  *(void**)(&method_set_display_visible) = Dlsym("SetDisplayVisible");
  if (method_set_display_visible) {
    return method_set_display_visible(player, is_visible);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetAudioMute(PlusPlayerRef player, bool is_mute) {
  PlusplayerSetAudioMute method_set_audio_mute;
  *(void**)(&method_set_audio_mute) = Dlsym("SetAudioMute");
  if (method_set_audio_mute) {
    return method_set_audio_mute(player, is_mute);
  }
  return false;
}

plusplayer::State PlusPlayerWrapperProxy::GetState(PlusPlayerRef player) {
  PlusplayerGetState method_get_state;
  *(void**)(&method_get_state) = Dlsym("GetState");
  if (method_get_state) {
    return method_get_state(player);
  }
  return plusplayer::State::kNone;
}

bool PlusPlayerWrapperProxy::GetDuration(PlusPlayerRef player,
                                         int64_t* duration_in_milliseconds) {
  PlusplayerGetDuration method_get_duration;
  *(void**)(&method_get_duration) = Dlsym("GetDuration");
  if (method_get_duration) {
    return method_get_duration(player, duration_in_milliseconds);
  }
  return false;
}

bool PlusPlayerWrapperProxy::GetPlayingTime(PlusPlayerRef player,
                                            uint64_t* time_in_milliseconds) {
  PlusplayerGetPlayingTime method_get_playing_time;
  *(void**)(&method_get_playing_time) = Dlsym("GetPlayingTime");
  if (method_get_playing_time) {
    return method_get_playing_time(player, time_in_milliseconds);
  }
  return false;
}

bool PlusPlayerWrapperProxy::SetPlaybackRate(PlusPlayerRef player,
                                             const double speed) {
  PlusplayerSetPlaybackRate method_set_playback_rate;
  *(void**)(&method_set_playback_rate) = Dlsym("SetPlaybackRate");
  if (method_set_playback_rate) {
    return method_set_playback_rate(player, speed);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Prepare(PlusPlayerRef player) {
  PlusplayerPrepare method_prepare;
  *(void**)(&method_prepare) = Dlsym("Prepare");
  if (method_prepare) {
    return method_prepare(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::PrepareAsync(PlusPlayerRef player) {
  PlusplayerPrepareAsync method_prepare_async;
  *(void**)(&method_prepare_async) = Dlsym("PrepareAsync");
  if (method_prepare_async) {
    return method_prepare_async(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Start(PlusPlayerRef player) {
  PlusplayerStart method_start;
  *(void**)(&method_start) = Dlsym("Start");
  if (method_start) {
    return method_start(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Stop(PlusPlayerRef player) {
  PlusplayerStop method_stop;
  *(void**)(&method_stop) = Dlsym("Stop");
  if (method_stop) {
    return method_stop(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Pause(PlusPlayerRef player) {
  PlusplayerPause method_pause;
  *(void**)(&method_pause) = Dlsym("Pause");
  if (method_pause) {
    return method_pause(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Resume(PlusPlayerRef player) {
  PlusplayerResume method_resume;
  *(void**)(&method_resume) = Dlsym("Resume");
  if (method_resume) {
    return method_resume(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Seek(PlusPlayerRef player,
                                  const uint64_t time_millisecond) {
  PlusplayerSeek method_seek;
  *(void**)(&method_seek) = Dlsym("Seek");
  if (method_seek) {
    return method_seek(player, time_millisecond);
  }
  return false;
}

void PlusPlayerWrapperProxy::SetStopPosition(PlusPlayerRef player,
                                             const uint64_t time_millisecond) {
  PlusplayerSetStopPosition method_set_stop_position;
  *(void**)(&method_set_stop_position) = Dlsym("SetStopPosition");
  if (method_set_stop_position) {
    method_set_stop_position(player, time_millisecond);
  }
}

bool PlusPlayerWrapperProxy::Suspend(PlusPlayerRef player) {
  PlusplayerSuspend method_suspend;
  *(void**)(&method_suspend) = Dlsym("Suspend");
  if (method_suspend) {
    return method_suspend(player);
  }
  return false;
}

bool PlusPlayerWrapperProxy::Restore(PlusPlayerRef player,
                                     plusplayer::State state) {
  PlusplayerRestore method_restore;
  *(void**)(&method_restore) = Dlsym("Restore");
  if (method_restore) {
    return method_restore(player, state);
  }
  return false;
}

bool PlusPlayerWrapperProxy::GetVideoSize(PlusPlayerRef player, int* width,
                                          int* height) {
  PlusplayerGetVideoSize method_get_video_size;
  *(void**)(&method_get_video_size) = Dlsym("GetVideoSize");
  if (method_get_video_size) {
    return method_get_video_size(player, width, height);
  }
  return false;
}

int PlusPlayerWrapperProxy::GetSurfaceId(PlusPlayerRef player, void* window) {
  PlusplayerGetSurfaceId method_get_surface_id;
  *(void**)(&method_get_surface_id) = Dlsym("GetSurfaceId");
  if (method_get_surface_id) {
    return method_get_surface_id(player, window);
  }
  return -1;
}

bool PlusPlayerWrapperProxy::Close(PlusPlayerRef player) {
  PlusplayerClose method_close;
  *(void**)(&method_close) = Dlsym("Close");
  if (method_close) {
    return method_close(player);
  }
  return false;
}

void PlusPlayerWrapperProxy::DestroyPlayer(PlusPlayerRef player) {
  PlusplayerDestroyPlayer method_destroy_player;
  *(void**)(&method_destroy_player) = Dlsym("DestroyPlayer");
  if (method_destroy_player) {
    method_destroy_player(player);
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
