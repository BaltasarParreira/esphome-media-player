  function hasDeviceProfile(group) {
    var profiles = WEB_DEVICE_PROFILES[group] || [];
    return profiles.indexOf(S.device_profile) !== -1;
  }

  function supportsTrackInfoDuration() {
    return hasDeviceProfile("track_info_duration");
  }

  function supportsScreenRotation() {
    return hasDeviceProfile("screen_rotation");
  }

  function supportsScreenTone() {
    return hasDeviceProfile("screen_tone");
  }

  function supportsClockScreenSaver() {
    return true;
  }
