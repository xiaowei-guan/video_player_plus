#include "video_player.h"

#include <app_manager.h>
#include <dlfcn.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/standard_method_codec.h>
#include <system_info.h>
//#include <Ecore_Wl2.h>

#include <unistd.h>

#include <cstdarg>
#include <functional>

#include "log.h"
#include "video_player_error.h"

static int gPlayerIndex = 1;

VideoPlayer::VideoPlayer(FlutterDesktopPluginRegistrarRef registrar_ref,
                         flutter::PluginRegistrar *plugin_registrar,
                         const std::string &uri, VideoPlayerOptions &options) {
  is_initialized_ = false;
  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  plusplayer_ = instance.CreatePlayer();
  if (plusplayer_ != nullptr) {
    instance.SetBufferingCallback(plusplayer_, onBuffering, this);
    instance.SetCompletedCallback(plusplayer_, onPlayCompleted, this);
    instance.SetPreparedCallback(plusplayer_, onPrepared, this);
    instance.SetSeekCompletedCallback(plusplayer_, onSeekCompleted, this);
    instance.SetErrorCallback(plusplayer_, onError, this);
    instance.SetErrorMessageCallback(plusplayer_, onErrorMessage, this);
    instance.SetAdaptiveStreamingControlCallback(
        plusplayer_, onPlayerAdaptiveStreamingControl, this);
    instance.SetDrmInitDataCallback(plusplayer_, onDrmInitData, this);
    LOG_DEBUG("[PlusPlayer]call Open to set uri (%s)", uri.c_str());
    if (!instance.Open(plusplayer_, uri.c_str())) {
      LOG_ERROR("Open uri(%s) failed", uri.c_str());
      throw VideoPlayerError("PlusPlayer", "Open failed");
    }
    LOG_DEBUG("[PlusPlayer]call SetAppId");
    char *appId = nullptr;
    long pid = getpid();
    int ret = app_manager_get_app_id(pid, &appId);
    if (ret == APP_MANAGER_ERROR_NONE) {
      LOG_DEBUG("set app id: %s", appId);
      instance.SetAppId(plusplayer_, appId);
    }
    if (appId) {
      free(appId);
    }
    LOG_DEBUG("[PlusPlayer]call RegisterListener");

    int w = 0;
    int h = 0;
    if (system_info_get_platform_int("http://tizen.org/feature/screen.width",
                                     &w) != SYSTEM_INFO_ERROR_NONE ||
        system_info_get_platform_int("http://tizen.org/feature/screen.height",
                                     &h) != SYSTEM_INFO_ERROR_NONE) {
      LOG_ERROR("Could not obtain the screen size.");
      throw VideoPlayerError("PlusPlayer", "Could not obtain the screen size");
    }
    LOG_DEBUG("[PlusPlayer]call SetDisplay");
    if (!instance.SetDisplay(
            plusplayer_, plusplayer::DisplayType::kOverlay,
            instance.GetSurfaceId(plusplayer_,
                                  FlutterDesktopGetWindow(registrar_ref)),
            0, 0, w, h)) {
      LOG_ERROR("Set display failed");
      throw VideoPlayerError("PlusPlayer", "set display failed");
    }
    LOG_DEBUG("[PlusPlayer]call SetDisplayMode");
    if (!instance.SetDisplayMode(plusplayer_,
                                 plusplayer::DisplayMode::kDstRoi)) {
      LOG_ERROR("set display mode failed");
      throw VideoPlayerError("PlusPlayer", "set display mode failed");
    }
    LOG_DEBUG("[PlusPlayer]call PrepareAsync");
    if (!instance.PrepareAsync(plusplayer_)) {
      LOG_ERROR("Parepare async failed");
      throw VideoPlayerError("PlusPlayer", "prepare async failed");
    }
  } else {
    LOG_ERROR("Create operation failed");
    throw VideoPlayerError("PlusPlayer", "Create operation failed");
  }
  texture_id_ = gPlayerIndex++;
  setupEventChannel(plugin_registrar->messenger());
}

void VideoPlayer::setDisplayRoi(int x, int y, int w, int h) {
  LOG_DEBUG("setDisplayRoi PlusPlayer x = %d, y = %d, w = %d, h = %d", x, y, w,
            h);
  if (plusplayer_ == nullptr) {
    LOG_ERROR("Plusplayer isn't created");
    throw VideoPlayerError("PlusPlayer", "Not created");
  }
  plusplayer::Geometry roi;
  roi.x = x;
  roi.y = y;
  roi.w = w;
  roi.h = h;
  bool ret =
      PlusPlayerWrapperProxy::GetInstance().SetDisplayRoi(plusplayer_, roi);

  if (!ret) {
    LOG_ERROR("Plusplayer SetDisplayRoi failed");
    throw VideoPlayerError("PlusPlayer", "SetDisplayRoi failed");
  }
}

VideoPlayer::~VideoPlayer() {
  LOG_INFO("[VideoPlayer] destructor");
  dispose();
}

long VideoPlayer::getTextureId() { return texture_id_; }

void VideoPlayer::play() {
  LOG_DEBUG("start PlusPlayer");
  if (plusplayer_ == nullptr) {
    LOG_ERROR("Plusplayer isn't created");
    throw VideoPlayerError("PlusPlayer", "Not created");
  }
  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  if (instance.GetState(plusplayer_) < plusplayer::State::kReady) {
    LOG_ERROR("Invalid state for play operation");
    throw VideoPlayerError("PlusPlayer", "Invalid state for play operation");
  }

  if (instance.GetState(plusplayer_) == plusplayer::State::kReady) {
    if (!instance.Start(plusplayer_)) {
      LOG_ERROR("Start operation failed");
      throw VideoPlayerError("PlusPlayer", "Start operation failed");
    }
  } else if (instance.GetState(plusplayer_) == plusplayer::State::kPaused) {
    if (!instance.Resume(plusplayer_)) {
      LOG_ERROR("Resume operation failed");
      throw VideoPlayerError("PlusPlayer", "Resume operation failed");
    }
  }
}

void VideoPlayer::pause() {
  LOG_DEBUG("pause PlusPlayer");
  if (plusplayer_ == nullptr) {
    LOG_ERROR("Plusplayer isn't created");
    throw VideoPlayerError("PlusPlayer", "Not created");
  }

  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  if (instance.GetState(plusplayer_) < plusplayer::State::kReady) {
    LOG_ERROR("Invalid state for pause operation");
    throw VideoPlayerError("PlusPlayer", "Invalid state for pause operation");
  }

  if (instance.GetState(plusplayer_) == plusplayer::State::kPlaying) {
    if (!instance.Pause(plusplayer_)) {
      LOG_ERROR("Pause operation failed");
      throw VideoPlayerError("PlusPlayer", "Pause operation failed");
    }
  }
}

void VideoPlayer::setLooping(bool is_looping) {
  LOG_ERROR("loop operation not supported");
}

void VideoPlayer::setVolume(double volume) {
  LOG_ERROR("PlusPlayer doesn't support to set volume");
}

void VideoPlayer::setPlaybackSpeed(double speed) {
  LOG_DEBUG("set playback speed: %f", speed);
  if (plusplayer_ == nullptr) {
    LOG_ERROR("Plusplayer isn't created");
    throw VideoPlayerError("PlusPlayer", "Not created");
  }
  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  if (!instance.SetPlaybackRate(plusplayer_, speed)) {
    LOG_ERROR("SetPlaybackRate failed");
    throw VideoPlayerError("PlusPlayer", "SetPlaybackRate operation failed");
  }
}

void VideoPlayer::seekTo(int position,
                         const SeekCompletedCb &seek_completed_cb) {
  LOG_DEBUG("seekTo position: %d", position);
  if (plusplayer_ == nullptr) {
    LOG_ERROR("Plusplayer isn't created");
    throw VideoPlayerError("PlusPlayer", "Not created");
  }
  on_seek_completed_ = seek_completed_cb;
  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  if (!instance.Seek(plusplayer_, (unsigned long long)position)) {
    on_seek_completed_ = nullptr;
    LOG_ERROR("Seek to position %d failed", position);
    throw VideoPlayerError("PlusPlayer", "Seek operation failed");
  }
}

int VideoPlayer::getPosition() {
  LOG_DEBUG("get video player position");
  if (plusplayer_ == nullptr) {
    LOG_ERROR("Plusplayer isn't created");
    throw VideoPlayerError("PlusPlayer", "Not created");
  }

  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  plusplayer::State state = instance.GetState(plusplayer_);
  if (state == plusplayer::State::kPlaying ||
      state == plusplayer::State::kPaused) {
    uint64_t position;
    instance.GetPlayingTime(plusplayer_, &position);
    LOG_DEBUG("playing time: %lld", position);
    return (int)position;
  } else {
    LOG_ERROR("Invalid state for GetPlayingTime operation");
    throw VideoPlayerError("PlusPlayer",
                           "Invalid state for GetPlayingTime operation");
  }
}

void VideoPlayer::dispose() {
  LOG_DEBUG("[VideoPlayer.dispose] dispose video player start");
  is_initialized_ = false;
  event_sink_ = nullptr;
  event_channel_->SetStreamHandler(nullptr);

  if (plusplayer_) {
    PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
    instance.UnsetBufferingCallback(plusplayer_);
    instance.UnsetCompletedCallback(plusplayer_);
    instance.UnsetPreparedCallback(plusplayer_);
    instance.UnsetSeekCompletedCallback(plusplayer_);
    instance.UnsetErrorCallback(plusplayer_);
    instance.UnsetErrorMessageCallback(plusplayer_);
    instance.UnsetAdaptiveStreamingControlCallback(plusplayer_);
    instance.UnsetDrmInitDataCallback(plusplayer_);
    instance.Stop(plusplayer_);
    instance.Close(plusplayer_);
    instance.DestroyPlayer(plusplayer_);
    plusplayer_ = nullptr;
  }
  LOG_DEBUG("[VideoPlayer.dispose] dispose video player end");
}

void VideoPlayer::setupEventChannel(flutter::BinaryMessenger *messenger) {
  LOG_DEBUG("[VideoPlayer.setupEventChannel] setup event channel");
  std::string name =
      "flutter.io/videoPlayer/videoEvents" + std::to_string(texture_id_);
  auto channel =
      std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
          messenger, name, &flutter::StandardMethodCodec::GetInstance());
  // SetStreamHandler be called after player_prepare,
  // because initialized event will be send in listen function of event channel
  auto handler = std::make_unique<
      flutter::StreamHandlerFunctions<flutter::EncodableValue>>(
      [&](const flutter::EncodableValue *arguments,
          std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> &&events)
          -> std::unique_ptr<
              flutter::StreamHandlerError<flutter::EncodableValue>> {
        LOG_DEBUG(
            "[VideoPlayer.setupEventChannel] call listen of StreamHandler");
        event_sink_ = std::move(events);
        initialize();
        return nullptr;
      },
      [&](const flutter::EncodableValue *arguments)
          -> std::unique_ptr<
              flutter::StreamHandlerError<flutter::EncodableValue>> {
        LOG_DEBUG(
            "[VideoPlayer.setupEventChannel] call cancel of StreamHandler");
        event_sink_ = nullptr;
        return nullptr;
      });
  channel->SetStreamHandler(std::move(handler));
  event_channel_ = std::move(channel);
}

void VideoPlayer::initialize() {
  PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
  plusplayer::State state = instance.GetState(plusplayer_);
  LOG_INFO("[VideoPlayer.initialize] player state: %d", state);
  if (state == plusplayer::State::kReady && !is_initialized_) {
    sendInitialized();
  }
}

void VideoPlayer::sendInitialized() {
  if (!is_initialized_ && event_sink_ != nullptr) {
    PlusPlayerWrapperProxy &instance = PlusPlayerWrapperProxy::GetInstance();
    int64_t duration;
    if (!instance.GetDuration(plusplayer_, &duration)) {
      LOG_ERROR("PlusPlayer - GetDuration operation failed");
      event_sink_->Error("PlusPlayer", "GetDuration operation failed");
      return;
    }
    LOG_DEBUG("[VideoPlayer.sendInitialized] video duration: %lld", duration);

    int width, height;
    if (!instance.GetVideoSize(plusplayer_, &width, &height)) {
      LOG_ERROR("PlusPlayer -> Get video size failed");
      event_sink_->Error("PlusPlayer", "Get video size failed");
      return;
    }
    LOG_DEBUG("video widht: %d, video height: %d", width, height);

    plusplayer::DisplayRotation rotate;
    if (!instance.GetDisplayRotate(plusplayer_, &rotate)) {
      LOG_ERROR("PlusPlayer - GetDisplayRotate operation failed");
      event_sink_->Error("PlusPlayer", "GetDisplayRotate operation failed");
    } else {
      if (rotate == plusplayer::DisplayRotation::kRotate90 ||
          rotate == plusplayer::DisplayRotation::kRotate270) {
        int tmp = width;
        width = height;
        height = tmp;
      }
    }

    is_initialized_ = true;
    flutter::EncodableMap encodables = {
        {flutter::EncodableValue("event"),
         flutter::EncodableValue("initialized")},
        {flutter::EncodableValue("duration"),
         flutter::EncodableValue(duration)},
        {flutter::EncodableValue("width"), flutter::EncodableValue(width)},
        {flutter::EncodableValue("height"), flutter::EncodableValue(height)}};
    flutter::EncodableValue eventValue(encodables);
    LOG_INFO("[VideoPlayer.sendInitialized] send initialized event");
    event_sink_->Success(eventValue);
  }
}

void VideoPlayer::sendBufferingStart() {
  if (event_sink_) {
    flutter::EncodableMap encodables = {
        {flutter::EncodableValue("event"),
         flutter::EncodableValue("bufferingStart")}};
    flutter::EncodableValue eventValue(encodables);
    LOG_INFO("[VideoPlayer.onBuffering] send bufferingStart event");
    event_sink_->Success(eventValue);
  }
}

void VideoPlayer::sendBufferingUpdate(int position) {
  if (event_sink_) {
    flutter::EncodableList range = {flutter::EncodableValue(0),
                                    flutter::EncodableValue(position)};
    flutter::EncodableList rangeList = {flutter::EncodableValue(range)};
    flutter::EncodableMap encodables = {
        {flutter::EncodableValue("event"),
         flutter::EncodableValue("bufferingUpdate")},
        {flutter::EncodableValue("values"),
         flutter::EncodableValue(rangeList)}};
    flutter::EncodableValue eventValue(encodables);
    LOG_INFO("[VideoPlayer.onBuffering] send bufferingUpdate event");
    event_sink_->Success(eventValue);
  }
}

void VideoPlayer::sendBufferingEnd() {
  if (event_sink_) {
    flutter::EncodableMap encodables = {
        {flutter::EncodableValue("event"),
         flutter::EncodableValue("bufferingEnd")}};
    flutter::EncodableValue eventValue(encodables);
    LOG_INFO("[VideoPlayer.onBuffering] send bufferingEnd event");
    event_sink_->Success(eventValue);
  }
}

void VideoPlayer::onPrepared(bool ret, void *data) {
  VideoPlayer *player = (VideoPlayer *)data;
  LOG_DEBUG("[VideoPlayer.onPrepared] video player is prepared");

  if (!player->is_initialized_) {
    player->sendInitialized();
  }
}

void VideoPlayer::onBuffering(int percent, void *data) {
  // percent isn't used for video size, it's the used storage of buffer
  LOG_DEBUG("[VideoPlayer.onBuffering] percent: %d", percent);
}

void VideoPlayer::onSeekCompleted(void *data) {
  VideoPlayer *player = (VideoPlayer *)data;
  LOG_DEBUG("[VideoPlayer.onSeekCompleted] completed to seek");

  if (player->on_seek_completed_) {
    player->on_seek_completed_();
    player->on_seek_completed_ = nullptr;
  }
}

void VideoPlayer::onPlayCompleted(void *data) {
  VideoPlayer *player = (VideoPlayer *)data;
  LOG_DEBUG("[VideoPlayer.onPlayCompleted] completed to play video");

  if (player->event_sink_) {
    flutter::EncodableMap encodables = {{flutter::EncodableValue("event"),
                                         flutter::EncodableValue("completed")}};
    flutter::EncodableValue eventValue(encodables);
    LOG_INFO("[VideoPlayer.onPlayCompleted] send completed event");
    player->event_sink_->Success(eventValue);

    LOG_DEBUG("[VideoPlayer.onPlayCompleted] change player state to pause");
    player->pause();
  }
}

void VideoPlayer::onPlaying(void *data) {}
void VideoPlayer::onError(const plusplayer::ErrorType &error_code,
                          void *user_data) {}
void VideoPlayer::onErrorMessage(const plusplayer::ErrorType &error_code,
                                 const char *error_msg, void *user_data) {}

void VideoPlayer::onPlayerAdaptiveStreamingControl(
    const plusplayer::StreamingMessageType &type,
    const plusplayer::MessageParam &msg, void *user_data) {}

void VideoPlayer::onDrmInitData(int *drmhandle, unsigned int len,
                                unsigned char *psshdata,
                                plusplayer::TrackType type, void *user_data) {}