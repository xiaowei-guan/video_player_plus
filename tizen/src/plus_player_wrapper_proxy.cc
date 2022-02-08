#include "plus_player_wrapper_proxy.h"

#include <dlfcn.h>

#include "log.h"

typedef PlusplayerRef (*PlusplayerCreatePlayer)();
typedef bool (*PlusplayerOpen)(PlusplayerRef player, const char* uri);
typedef void (*PlusplayerSetAppId)(PlusplayerRef player, const char* app_id);
typedef void (*PlusplayerSetPrebufferMode)(PlusplayerRef player,
                                           bool is_prebuffer_mode);
typedef bool (*PlusplayerStopSource)(PlusplayerRef player);
typedef bool (*PlusplayerSetDisplay)(PlusplayerRef player,
                                     const plusplayer::DisplayType& type,
                                     const uint32_t serface_id, const int x,
                                     const int y, const int w, const int h);
typedef bool (*PlusplayerSetDisplayMode)(PlusplayerRef player,
                                         const plusplayer::DisplayMode& mode);
typedef bool (*PlusplayerSetDisplayRoi)(PlusplayerRef player,
                                        const plusplayer::Geometry& roi);
typedef bool (*PlusplayerSetDisplayRotate)(
    PlusplayerRef player, const plusplayer::DisplayRotation& rotate);
typedef bool (*PlusplayerGetDisplayRotate)(PlusplayerRef player,
                                           plusplayer::DisplayRotation* rotate);
typedef bool (*PlusplayerSetDisplayVisible)(PlusplayerRef player,
                                            bool is_visible);
typedef bool (*PlusplayerSetAudioMute)(PlusplayerRef player, bool is_mute);
typedef plusplayer::State (*PlusplayerGetState)(PlusplayerRef player);
typedef bool (*PlusplayerGetDuration)(PlusplayerRef player,
                                      int64_t* duration_in_milliseconds);
typedef bool (*PlusplayerGetPlayingTime)(PlusplayerRef player,
                                         uint64_t* time_in_milliseconds);
typedef bool (*PlusplayerSetPlaybackRate)(PlusplayerRef player,
                                          const double speed);
typedef bool (*PlusplayerPrepare)(PlusplayerRef player);
typedef bool (*PlusplayerPrepareAsync)(PlusplayerRef player);
typedef bool (*PlusplayerStart)(PlusplayerRef player);
typedef bool (*PlusplayerStop)(PlusplayerRef player);
typedef bool (*PlusplayerPause)(PlusplayerRef player);
typedef bool (*PlusplayerResume)(PlusplayerRef player);
typedef bool (*PlusplayerSeek)(PlusplayerRef player,
                               const uint64_t time_millisecond);
typedef bool (*PlusplayerSetStopPosition)(PlusplayerRef player,
                                          const uint64_t time_millisecond);
typedef bool (*PlusplayerSuspend)(PlusplayerRef player);
typedef bool (*PlusplayerRestore)(PlusplayerRef player,
                                  plusplayer::State state);
typedef bool (*PlusplayerGetVideoSize)(PlusplayerRef player, int* width,
                                       int* height);
typedef int (*PlusplayerGetSurfaceId)(PlusplayerRef player, void* window);
typedef bool (*PlusplayerClose)(PlusplayerRef player);
typedef void (*PlusplayerDestroyPlayer)(PlusplayerRef player);
typedef void (*PlusplayerRegisterListener)(PlusplayerRef player,
                                           PlusplayerListener* listener,
                                           void* user_data);
typedef void (*PlusplayerUnregisterListener)(PlusplayerRef player);
typedef void (*PlusplayerSetDrm)(PlusplayerRef player,
                                 const plusplayer::drm::Property& property);
typedef void (*PlusplayerDrmLicenseAcquiredDone)(PlusplayerRef player,
                                                 plusplayer::TrackType type);

PlusplayerWrapperProxy::PlusplayerWrapperProxy() {
  plus_player_hander_ = dlopen("libplus_player_wrapper.so", RTLD_LAZY);
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed %s: ", dlerror());
  }
}
PlusplayerWrapperProxy::~PlusplayerWrapperProxy() {
  LOG_ERROR("~PlusplayerWrapperProxy");
  if (plus_player_hander_) {
    dlclose(plus_player_hander_);
    plus_player_hander_ = nullptr;
  }
}

void* PlusplayerWrapperProxy::Dlsym(const char* name) {
  if (!plus_player_hander_) {
    LOG_ERROR("dlopen failed plus_player_hander_ is null");
    return nullptr;
  }
  return dlsym(plus_player_hander_, name);
}

PlusplayerRef PlusplayerWrapperProxy::CreatePlayer() {
  PlusplayerCreatePlayer method_create_player;
  *(void**)(&method_create_player) = Dlsym("CreatePlayer");
  if (method_create_player) {
    return method_create_player();
  }
  return nullptr;
}

bool PlusplayerWrapperProxy::Open(PlusplayerRef player, const char* uri) {
  PlusplayerOpen method_open;
  *(void**)(&method_open) = Dlsym("Open");
  if (method_open) {
    return method_open(player, uri);
  }
  return false;
}

void PlusplayerWrapperProxy::SetAppId(PlusplayerRef player,
                                      const char* app_id) {
  PlusplayerSetAppId method_set_app_id;
  *(void**)(&method_set_app_id) = Dlsym("SetAppId");
  if (method_set_app_id) {
    method_set_app_id(player, app_id);
  }
}

void PlusplayerWrapperProxy::SetPrebufferMode(PlusplayerRef player,
                                              bool is_prebuffer_mode) {
  PlusplayerSetPrebufferMode method_set_prebuffer_mode;
  *(void**)(&method_set_prebuffer_mode) = Dlsym("SetPrebufferMode");
  if (method_set_prebuffer_mode) {
    method_set_prebuffer_mode(player, is_prebuffer_mode);
  }
}

bool PlusplayerWrapperProxy::StopSource(PlusplayerRef player) {
  PlusplayerStopSource method_stop_source;
  *(void**)(&method_stop_source) = Dlsym("StopSource");
  if (method_stop_source) {
    return method_stop_source(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::SetDisplay(PlusplayerRef player,
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

bool PlusplayerWrapperProxy::SetDisplayMode(
    PlusplayerRef player, const plusplayer::DisplayMode& mode) {
  PlusplayerSetDisplayMode method_set_display_mode;
  *(void**)(&method_set_display_mode) = Dlsym("SetDisplayMode");
  if (method_set_display_mode) {
    return method_set_display_mode(player, mode);
  }
  return false;
}

bool PlusplayerWrapperProxy::SetDisplayRoi(PlusplayerRef player,
                                           const plusplayer::Geometry& roi) {
  PlusplayerSetDisplayRoi method_set_display_roi;
  *(void**)(&method_set_display_roi) = Dlsym("SetDisplayRoi");
  if (method_set_display_roi) {
    return method_set_display_roi(player, roi);
  }
  return false;
}

bool PlusplayerWrapperProxy::SetDisplayRotate(
    PlusplayerRef player, const plusplayer::DisplayRotation& rotate) {
  PlusplayerSetDisplayRotate method_set_display_rotate;
  *(void**)(&method_set_display_rotate) = Dlsym("SetDisplayRotate");
  if (method_set_display_rotate) {
    return method_set_display_rotate(player, rotate);
  }
  return false;
}

bool PlusplayerWrapperProxy::GetDisplayRotate(
    PlusplayerRef player, plusplayer::DisplayRotation* rotate) {
  PlusplayerGetDisplayRotate method_get_display_rotate;
  *(void**)(&method_get_display_rotate) = Dlsym("GetDisplayRotate");
  if (method_get_display_rotate) {
    return method_get_display_rotate(player, rotate);
  }
  return false;
}

bool PlusplayerWrapperProxy::SetDisplayVisible(PlusplayerRef player,
                                               bool is_visible) {
  PlusplayerSetDisplayVisible method_set_display_visible;
  *(void**)(&method_set_display_visible) = Dlsym("SetDisplayVisible");
  if (method_set_display_visible) {
    return method_set_display_visible(player, is_visible);
  }
  return false;
}

bool PlusplayerWrapperProxy::SetAudioMute(PlusplayerRef player, bool is_mute) {
  PlusplayerSetAudioMute method_set_audio_mute;
  *(void**)(&method_set_audio_mute) = Dlsym("SetAudioMute");
  if (method_set_audio_mute) {
    return method_set_audio_mute(player, is_mute);
  }
  return false;
}

plusplayer::State PlusplayerWrapperProxy::GetState(PlusplayerRef player) {
  PlusplayerGetState method_get_state;
  *(void**)(&method_get_state) = Dlsym("GetState");
  if (method_get_state) {
    return method_get_state(player);
  }
  return plusplayer::State::kNone;
}

bool PlusplayerWrapperProxy::GetDuration(PlusplayerRef player,
                                         int64_t* duration_in_milliseconds) {
  PlusplayerGetDuration method_get_duration;
  *(void**)(&method_get_duration) = Dlsym("GetDuration");
  if (method_get_duration) {
    return method_get_duration(player, duration_in_milliseconds);
  }
  return false;
}

bool PlusplayerWrapperProxy::GetPlayingTime(PlusplayerRef player,
                                            uint64_t* time_in_milliseconds) {
  PlusplayerGetPlayingTime method_get_playing_time;
  *(void**)(&method_get_playing_time) = Dlsym("GetPlayingTime");
  if (method_get_playing_time) {
    return method_get_playing_time(player, time_in_milliseconds);
  }
  return false;
}

bool PlusplayerWrapperProxy::SetPlaybackRate(PlusplayerRef player,
                                             const double speed) {
  PlusplayerSetPlaybackRate method_set_playback_rate;
  *(void**)(&method_set_playback_rate) = Dlsym("SetPlaybackRate");
  if (method_set_playback_rate) {
    return method_set_playback_rate(player, speed);
  }
  return false;
}

bool PlusplayerWrapperProxy::Prepare(PlusplayerRef player) {
  PlusplayerPrepare method_prepare;
  *(void**)(&method_prepare) = Dlsym("Prepare");
  if (method_prepare) {
    return method_prepare(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::PrepareAsync(PlusplayerRef player) {
  PlusplayerPrepareAsync method_prepare_async;
  *(void**)(&method_prepare_async) = Dlsym("PrepareAsync");
  if (method_prepare_async) {
    return method_prepare_async(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::Start(PlusplayerRef player) {
  PlusplayerStart method_start;
  *(void**)(&method_start) = Dlsym("Start");
  if (method_start) {
    return method_start(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::Stop(PlusplayerRef player) {
  PlusplayerStop method_stop;
  *(void**)(&method_stop) = Dlsym("Stop");
  if (method_stop) {
    return method_stop(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::Pause(PlusplayerRef player) {
  PlusplayerPause method_pause;
  *(void**)(&method_pause) = Dlsym("Pause");
  if (method_pause) {
    return method_pause(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::Resume(PlusplayerRef player) {
  PlusplayerResume method_resume;
  *(void**)(&method_resume) = Dlsym("Resume");
  if (method_resume) {
    return method_resume(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::Seek(PlusplayerRef player,
                                  const uint64_t time_millisecond) {
  PlusplayerSeek method_seek;
  *(void**)(&method_seek) = Dlsym("Seek");
  if (method_seek) {
    return method_seek(player, time_millisecond);
  }
  return false;
}

void PlusplayerWrapperProxy::SetStopPosition(PlusplayerRef player,
                                             const uint64_t time_millisecond) {
  PlusplayerSetStopPosition method_set_stop_position;
  *(void**)(&method_set_stop_position) = Dlsym("SetStopPosition");
  if (method_set_stop_position) {
    method_set_stop_position(player, time_millisecond);
  }
}

bool PlusplayerWrapperProxy::Suspend(PlusplayerRef player) {
  PlusplayerSuspend method_suspend;
  *(void**)(&method_suspend) = Dlsym("Suspend");
  if (method_suspend) {
    return method_suspend(player);
  }
  return false;
}

bool PlusplayerWrapperProxy::Restore(PlusplayerRef player,
                                     plusplayer::State state) {
  PlusplayerRestore method_restore;
  *(void**)(&method_restore) = Dlsym("Restore");
  if (method_restore) {
    return method_restore(player, state);
  }
  return false;
}

bool PlusplayerWrapperProxy::GetVideoSize(PlusplayerRef player, int* width,
                                          int* height) {
  PlusplayerGetVideoSize method_get_video_size;
  *(void**)(&method_get_video_size) = Dlsym("GetVideoSize");
  if (method_get_video_size) {
    return method_get_video_size(player, width, height);
  }
  return false;
}

int PlusplayerWrapperProxy::GetSurfaceId(PlusplayerRef player, void* window) {
  PlusplayerGetSurfaceId method_get_surface_id;
  *(void**)(&method_get_surface_id) = Dlsym("GetSurfaceId");
  if (method_get_surface_id) {
    return method_get_surface_id(player, window);
  }
  return -1;
}

bool PlusplayerWrapperProxy::Close(PlusplayerRef player) {
  PlusplayerClose method_close;
  *(void**)(&method_close) = Dlsym("Close");
  if (method_close) {
    return method_close(player);
  }
  return false;
}

void PlusplayerWrapperProxy::DestroyPlayer(PlusplayerRef player) {
  PlusplayerDestroyPlayer method_destroy_player;
  *(void**)(&method_destroy_player) = Dlsym("DestroyPlayer");
  if (method_destroy_player) {
    method_destroy_player(player);
  }
}

void PlusplayerWrapperProxy::SetDrm(PlusplayerRef player,
                                    const plusplayer::drm::Property& property) {
  PlusplayerSetDrm method_set_drm;
  *(void**)(&method_set_drm) = Dlsym("SetDrm");
  if (method_set_drm) {
    method_set_drm(player, property);
  }
}

void PlusplayerWrapperProxy::DrmLicenseAcquiredDone(
    PlusplayerRef player, plusplayer::TrackType type) {
  PlusplayerDrmLicenseAcquiredDone method_drm_licenseAcquire_done;
  *(void**)(&method_drm_licenseAcquire_done) = Dlsym("DrmLicenseAcquiredDone");
  if (method_drm_licenseAcquire_done) {
    method_drm_licenseAcquire_done(player, type);
  }
}

void PlusplayerWrapperProxy::RegisterListener(PlusplayerRef player,
                                              PlusplayerListener* listener,
                                              void* user_data) {
  PlusplayerRegisterListener method_register_listener;
  *(void**)&method_register_listener = Dlsym("RegisterListener");
  if (method_register_listener) {
    method_register_listener(player, listener, user_data);
  }
}

void PlusplayerWrapperProxy::UnregisterListener(PlusplayerRef player) {
  PlusplayerUnregisterListener method_unregister_listener;
  *(void**)&method_unregister_listener = Dlsym("RegisterListener");
  if (method_unregister_listener) {
    method_unregister_listener(player);
  }
}
