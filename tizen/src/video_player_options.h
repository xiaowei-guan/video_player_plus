#ifndef VIDEO_PLAYER_OPTIONS_H_
#define VIDEO_PLAYER_OPTIONS_H_

class VideoPlayerOptions {
 public:
  VideoPlayerOptions() : mixWithOthers_(true) {}
  ~VideoPlayerOptions() = default;

  VideoPlayerOptions(const VideoPlayerOptions &other) = default;
  VideoPlayerOptions &operator=(const VideoPlayerOptions &other) = default;

  void setMixWithOthers(bool mixWithOthers) { mixWithOthers_ = mixWithOthers; }
  bool getMixWithOthers() const { return mixWithOthers_; }
  void setDrmOptions(const int drm_type,
                     const std::string &license_server_url) {
    drmType_ = drm_type;
    licenseServerUrl_ = license_server_url;
  }
  int getDrmType() { return drmType_; }
  const char *getLicenseServerUrl() { return licenseServerUrl_.c_str(); }

 private:
  bool mixWithOthers_;
  int drmType_;
  std::string licenseServerUrl_;
};

#endif  // VIDEO_PLAYER_OPTIONS_H_
