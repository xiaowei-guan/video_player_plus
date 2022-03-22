#ifndef VIDEO_PLAYER_H_
#define VIDEO_PLAYER_H_

#include <flutter/encodable_value.h>
#include <flutter/event_channel.h>
#include <flutter/plugin_registrar.h>
#include <flutter_tizen.h>
#include <glib.h>

#include "drm_manager.h"
//#include <player_product.h>

#include <mutex>
#include <string>

#include "plus_player_wrapper_proxy.h"
#include "video_player_options.h"

typedef enum {
  PLUS_PLAYER_STATE_NONE,    /**< Player is not created */
  PLUS_PLAYER_STATE_IDLE,    /**< Player is created, but not prepared */
  PLUS_PLAYER_STATE_READY,   /**< Player is ready to play media */
  PLUS_PLAYER_STATE_PLAYING, /**< Player is playing media */
  PLUS_PLAYER_STATE_PAUSED,  /**< Player is paused while playing media */
} plusplayer_state_e;

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
  // DRM Function
  void m_InitializeDrmSession(const std::string &uri, int nDrmType);
  void m_ReleaseDrmSession();
  static void m_CbDrmManagerError(long errCode, char *errMsg, void *userData);
  static int m_CbChallengeData(void *session_id, int msgType, void *msg,
                               int msgLen, void *userData);
  static gboolean m_InstallEMEKey(void *pData);

  unsigned char *m_pbResponse;
  SetDataParam_t m_licenseparam;
  DRMSessionHandle_t m_DRMSession;
  int m_DrmType;
  unsigned int m_sourceId;
  std::string m_LicenseUrl;
  // end DRM

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
  void *drm_manager_handle_ = nullptr;
};

#endif  // VIDEO_PLAYER_H_
