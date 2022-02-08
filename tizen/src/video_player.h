#ifndef VIDEO_PLAYER_H_
#define VIDEO_PLAYER_H_

#include <flutter/encodable_value.h>
#include <flutter/event_channel.h>
#include <flutter/plugin_registrar.h>
#include <flutter_tizen.h>

#include <mutex>
#include <string>

#include "plus_player_wrapper_proxy.h"
#include "video_player_options.h"

using SeekCompletedCb = std::function<void()>;

class VideoPlayer {
 public:
  VideoPlayer(FlutterDesktopPluginRegistrarRef registrar_ref,
              flutter::PluginRegistrar *plugin_registrar,
              const std::string &uri, VideoPlayerOptions &options);
  ~VideoPlayer();

  long getTextureId();
  void play();
  void pause();
  void setLooping(bool is_looping);
  void setVolume(double volume);
  void setPlaybackSpeed(double speed);
  void seekTo(int position,
              const SeekCompletedCb &seek_completed_cb);  // milliseconds
  int getPosition();                                      // milliseconds
  void dispose();
  void setDisplayRoi(int x, int y, int w, int h);

 private:
  void initialize();
  void setupEventChannel(flutter::BinaryMessenger *messenger);
  void sendInitialized();
  void sendBufferingStart();
  void sendBufferingUpdate(int position);  // milliseconds
  void sendBufferingEnd();
  void sendSeeking(bool seeking);

  static void onPrepared(bool ret, void *data);
  static void onBuffering(int percent, void *data);
  static void onSeekCompleted(void *data);
  static void onPlayCompleted(void *data);
  static void onPlaying(void *data);
  static void onError(const plusplayer::ErrorType &error_code, void *user_data);
  static void onErrorMessage(const plusplayer::ErrorType &error_code,
                             const char *error_msg, void *user_data);
  static void onPlayerAdaptiveStreamingControl(
      const plusplayer::StreamingMessageType &type,
      const plusplayer::MessageParam &msg, void *user_data);

  static void onDrmInitData(int *drmhandle, unsigned int len,
                            unsigned char *psshdata, plusplayer::TrackType type,
                            void *user_data);

  bool is_initialized_;
  std::unique_ptr<flutter::EventChannel<flutter::EncodableValue>>
      event_channel_;
  std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> event_sink_;
  long texture_id_;
  PlusplayerRef plusplayer_{nullptr};
  SeekCompletedCb on_seek_completed_;
  PlusplayerListener listener_;
};

#endif  // VIDEO_PLAYER_H_
