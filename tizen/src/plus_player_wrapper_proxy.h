#ifndef PLUS_PLAYER_WRAPPER_H_
#define PLUS_PLAYER_WRAPPER_H_

#include <stddef.h>
#include <stdint.h>
#include <tizen_error.h>

#include <string>

#define PLUSPLAYER_ERROR_CLASS TIZEN_ERROR_PLAYER | 0x20

/* This is for custom defined player error. */
#define PLUSPLAYER_CUSTOM_ERROR_CLASS TIZEN_ERROR_PLAYER | 0x1000

namespace plusplayer {

enum class DisplayType { kNone, kOverlay, kEvas, kMixer };

enum class DisplayMode {
  kLetterBox,
  kOriginSize,
  kFullScreen,
  kCroppedFull,
  kOriginOrLetter,
  kDstRoi,
  kAutoAspectRatio,
  kMax
};

enum TrackType {
  kTrackTypeAudio = 0,
  kTrackTypeVideo,
  kTrackTypeSubtitle,
  kTrackTypeMax
};

enum class DisplayRotation { kNone, kRotate90, kRotate180, kRotate270 };

enum class State {
  kNone, /**< Player is created, but not opened */
  kIdle, /**< Player is opened, but not prepared or player is stopped */
  kTypeFinderReady,  /**< TypeFinder prepared */
  kTrackSourceReady, /**< TrackSource prepared */
  kReady,            /**< Player is ready to play(start) */
  kPlaying,          /**< Player is playing media */
  kPaused            /**< Player is paused while playing media */
};

struct Geometry {
  int x = 0, y = 0;
  int w = 1920, h = 1080;
};

enum class ErrorType {
  kNone = TIZEN_ERROR_NONE,                          /**< Successful */
  kOutOfMemory = TIZEN_ERROR_OUT_OF_MEMORY,          /**< Out of memory */
  kInvalidParameter = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
  kNoSuchFile = TIZEN_ERROR_NO_SUCH_FILE, /**< No such file or directory */
  kInvalidOperation = TIZEN_ERROR_INVALID_OPERATION, /**< Invalid operation */
  kFileNoSpaceOnDevice =
      TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE, /**< No space left on the device */
  kFeatureNotSupportedOnDevice =
      TIZEN_ERROR_NOT_SUPPORTED,                 /**< Not supported */
  kSeekFailed = PLUSPLAYER_ERROR_CLASS | 0x01,   /**< Seek operation failure */
  kInvalidState = PLUSPLAYER_ERROR_CLASS | 0x02, /**< Invalid state */
  kNotSupportedFile =
      PLUSPLAYER_ERROR_CLASS | 0x03,           /**< File format not supported */
  kInvalidUri = PLUSPLAYER_ERROR_CLASS | 0x04, /**< Invalid URI */
  kSoundPolicy = PLUSPLAYER_ERROR_CLASS | 0x05, /**< Sound policy error */
  kConnectionFailed =
      PLUSPLAYER_ERROR_CLASS | 0x06, /**< Streaming connection failed */
  kVideoCaptureFailed =
      PLUSPLAYER_ERROR_CLASS | 0x07,             /**< Video capture failed */
  kDrmExpired = PLUSPLAYER_ERROR_CLASS | 0x08,   /**< Expired license */
  kDrmNoLicense = PLUSPLAYER_ERROR_CLASS | 0x09, /**< No license */
  kDrmFutureUse = PLUSPLAYER_ERROR_CLASS | 0x0a, /**< License for future use */
  kDrmNotPermitted = PLUSPLAYER_ERROR_CLASS | 0x0b, /**< Format not permitted */
  kResourceLimit = PLUSPLAYER_ERROR_CLASS | 0x0c,   /**< Resource limit */
  kPermissionDenied = TIZEN_ERROR_PERMISSION_DENIED, /**< Permission denied */
  kServiceDisconnected =
      PLUSPLAYER_ERROR_CLASS | 0x0d, /**< Socket connection lost (Since 3.0) */
  kBufferSpace =
      TIZEN_ERROR_BUFFER_SPACE, /**< No buffer space available (Since 3.0)*/
  kNotSupportedAudioCodec =
      PLUSPLAYER_ERROR_CLASS | 0x0e, /**< Not supported audio codec but video
                                        can be played (Since 4.0) */
  kNotSupportedVideoCodec =
      PLUSPLAYER_ERROR_CLASS | 0x0f, /**< Not supported video codec but audio
                                        can be played (Since 4.0) */
  kNotSupportedSubtitle =
      PLUSPLAYER_ERROR_CLASS |
      0x10, /**< Not supported subtitle format (Since 4.0) */

  // TODO(euna7.ko) Can be removed. refer to
  // http://168.219.243.246:8090/pages/viewpage.action?pageId=27269511
  kDrmInfo =
      PLUSPLAYER_CUSTOM_ERROR_CLASS | 0x05, /**< playready drm error info */
  kNotSupportedFormat = PLUSPLAYER_CUSTOM_ERROR_CLASS | 0x08,
  kStreamingPlayer = PLUSPLAYER_CUSTOM_ERROR_CLASS | 0x09,
  kDtcpFsk = PLUSPLAYER_CUSTOM_ERROR_CLASS | 0x0a,
  kPreLoadingTimeOut = PLUSPLAYER_CUSTOM_ERROR_CLASS |
                       0x0b, /**< can't finish preloading in time*/
  kNetworkError =
      PLUSPLAYER_CUSTOM_ERROR_CLASS | 0x0c, /**< for network error */
  kChannelSurfingFailed =
      PLUSPLAYER_CUSTOM_ERROR_CLASS | 0x0d, /**< for channel surfing error */

  kUnknown
};

enum class StreamingMessageType {
  kNone = 0,
  // kResolutionChanged,
  // kAdEnd,
  // kAdStart,
  // kRenderDone,
  kBitrateChange,
  // kFragmentInfo,
  kSparseTrackDetect,
  // kStreamingEvent,
  // kDrmChallengeData,
  kDrmInitData,
  // kHttpErrorCode,
  // kDrmRenewSessionData,
  kStreamEventType,
  kStreamEventData,
  kStreamSyncFlush,
  kStreamMrsUrlChanged,
  kDrmKeyRotation,
  kFragmentDownloadInfo,
  kDvrLiveLag,
  kSparseTrackData,
  kConnectionRetry,
  kConfigLowLatency,
  kCurlErrorDebugInfo
};

struct MessageParam {
  std::string data;
  int size = 0;
  int code = 0;  // Error or warning code
};

namespace drm {
using LicenseAcquiredCb = void*;
using UserData = void*;
using DrmHandle = int;

enum class Type {
  kNone = 0,
  kPlayready,
  kMarlin,
  kVerimatrix,
  kWidevineClassic,
  kSecuremedia,
  kSdrm,
  kWidevineCdm = 8,
  kMax
};
struct Property {
  Type type = Type::kNone;           // Drm type
  DrmHandle handle = 0;              // Drm handle
  bool external_decryption = false;  // External Decryption Mode
  LicenseAcquiredCb license_acquired_cb =
      nullptr;  // The cb will be invoked when license was acquired.
  UserData license_acquired_userdata =
      nullptr;  // The userdata will be sent by license_acquired_cb
};
}  // namespace drm

}  // namespace plusplayer

struct PlusPlayer;
typedef struct PlusPlayer* PlusPlayerRef;

typedef void (*OnPlayerPrepared)(bool ret, void* user_data);
typedef void (*OnPlayerSeekCompleted)(void* user_data);
typedef void (*OnPlayerResourceConflicted)(void* user_data);
typedef void (*OnPlayerBuffering)(int percent, void* user_data);
typedef void (*OnPlayerCompleted)(void* user_data);
typedef void (*OnPlayerPlaying)(void* user_data);
typedef void (*OnPlayerError)(const plusplayer::ErrorType& error_code,
                              void* user_data);
typedef void (*OnPlayerErrorMessage)(const plusplayer::ErrorType& error_code,
                                     const char* error_msg, void* user_data);
typedef void (*OnPlayerAdaptiveStreamingControl)(
    const plusplayer::StreamingMessageType& type,
    const plusplayer::MessageParam& msg, void* user_data);

typedef void (*OnPlayerDrmInitData)(int* drmhandle, unsigned int len,
                                    unsigned char* psshdata, plusplayer::TrackType type,
                                    void* user_data);

class PlusPlayerWrapperProxy {
 public:
  static PlusPlayerWrapperProxy& GetInstance() {
    static PlusPlayerWrapperProxy instance;
    return instance;
  }

  ~PlusPlayerWrapperProxy();
  PlusPlayerWrapperProxy(const PlusPlayerWrapperProxy&) = delete;
  PlusPlayerWrapperProxy& operator=(const PlusPlayerWrapperProxy&) = delete;

  PlusPlayerRef CreatePlayer();

  bool Open(PlusPlayerRef player, const char* uri);

  bool Close(PlusPlayerRef player);

  void SetAppId(PlusPlayerRef player, const char* app_id);

  void SetPrebufferMode(PlusPlayerRef player, bool is_prebuffer_mode);

  bool StopSource(PlusPlayerRef player);

  bool SetDisplay(PlusPlayerRef player, const plusplayer::DisplayType& type,
                  const uint32_t serface_id, const int x, const int y,
                  const int w, const int h);

  bool SetDisplayMode(PlusPlayerRef player,
                      const plusplayer::DisplayMode& mode);
  bool SetDisplayRoi(PlusPlayerRef player, const plusplayer::Geometry& roi);

  bool SetDisplayRotate(PlusPlayerRef player,
                        const plusplayer::DisplayRotation& rotate);

  bool GetDisplayRotate(PlusPlayerRef player,
                        plusplayer::DisplayRotation* rotate);

  bool SetDisplayVisible(PlusPlayerRef player, bool is_visible);

  bool SetAudioMute(PlusPlayerRef player, bool is_mute);

  plusplayer::State GetState(PlusPlayerRef player);

  bool GetDuration(PlusPlayerRef player, int64_t* duration_in_milliseconds);

  bool GetPlayingTime(PlusPlayerRef player, uint64_t* time_in_milliseconds);
  bool SetPlaybackRate(PlusPlayerRef player, const double speed);

  bool Prepare(PlusPlayerRef player);

  bool PrepareAsync(PlusPlayerRef player);
  bool Start(PlusPlayerRef player);

  bool Stop(PlusPlayerRef player);

  bool Pause(PlusPlayerRef player);

  bool Resume(PlusPlayerRef player);

  bool Seek(PlusPlayerRef player, const uint64_t time_millisecond);

  void SetStopPosition(PlusPlayerRef player, const uint64_t time_millisecond);

  bool Suspend(PlusPlayerRef player);

  bool Restore(PlusPlayerRef player, plusplayer::State state);

  bool GetVideoSize(PlusPlayerRef player, int* width, int* height);

  void DestroyPlayer(PlusPlayerRef player);

  void SetCompletedCallback(PlusPlayerRef player, OnPlayerCompleted callback,
                            void* user_data);

  void UnsetCompletedCallback(PlusPlayerRef player);

  void SetBufferingCallback(PlusPlayerRef player, OnPlayerBuffering callback,
                            void* user_data);

  void UnsetBufferingCallback(PlusPlayerRef player);

  void SetPreparedCallback(PlusPlayerRef player, OnPlayerPrepared callback,
                           void* user_data);

  void UnsetPreparedCallback(PlusPlayerRef player);

  void SetResourceConflictedCallback(PlusPlayerRef player,
                                     OnPlayerResourceConflicted callback,
                                     void* user_data);

  void UnsetResourceConflictedCallback(PlusPlayerRef player);

  void SetPlayingCallback(PlusPlayerRef player, OnPlayerPlaying callback,
                          void* user_data);

  void UnsetPlayingCallback(PlusPlayerRef player);

  int GetSurfaceId(PlusPlayerRef player, void* window);
  void SetErrorCallback(PlusPlayerRef player, OnPlayerError callback,
                        void* user_data);

  void UnsetErrorCallback(PlusPlayerRef player);

  void SetErrorMessageCallback(PlusPlayerRef player,
                               OnPlayerErrorMessage callback, void* user_data);

  void UnsetErrorMessageCallback(PlusPlayerRef player);

  void SetSeekCompletedCallback(PlusPlayerRef player,
                                OnPlayerSeekCompleted callback,
                                void* user_data);

  void UnsetSeekCompletedCallback(PlusPlayerRef player);

  void SetAdaptiveStreamingControlCallback(
      PlusPlayerRef player, OnPlayerAdaptiveStreamingControl callback,
      void* user_data);

  void UnsetAdaptiveStreamingControlCallback(PlusPlayerRef player);

  void SetDrm(PlusPlayerRef player, const plusplayer::drm::Property& property);
  void DrmLicenseAcquiredDone(PlusPlayerRef player, plusplayer::TrackType type);

void SetDrmInitDataCallback(PlusPlayerRef player, OnPlayerDrmInitData callback,
                            void* user_data);

void UnsetDrmInitDataCallback(PlusPlayerRef player);

 private:
  PlusPlayerWrapperProxy();
  void* plus_player_hander_{nullptr};
};
#endif