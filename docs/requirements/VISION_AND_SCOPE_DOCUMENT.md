# Vision and Scope Document

## SimpleTuner

## 1. Business Requirements

### 1.1 Background

Musical instrument tuning is a fundamental requirement for musicians of all skill levels. While hardware tuners and web-based solutions exist, there is a persistent need for reliable, offline mobile tuner applications that work without internet connectivity. Musicians require accurate pitch detection and reference tones during practice sessions, rehearsals, and performances—often in environments without reliable network access.

The JUCE framework provides cross-platform audio capabilities suitable for developing a professional-grade tuner that maintains consistent behavior across iOS and Android devices while minimizing platform-specific implementation complexity.

### 1.2 Business Opportunity

**BO-1:** Provide a free, high-quality chromatic tuner accessible to musicians worldwide without subscription fees or network requirements.

**BO-2:** Fill the gap for musicians who need offline functionality during travel, outdoor performances, or in locations with limited connectivity.

**BO-3:** Serve both casual musicians who need basic tuning assistance and professional musicians who require precise calibration and reference tone capabilities.

### 1.3 Business Objectives

**OBJ-1:** Release a production-ready chromatic tuner application on iOS and Android app stores within 2 months of project initiation.

**OBJ-2:** Maintain application size under 25 MB to minimize download barriers and device storage requirements.

**OBJ-3:** Ensure 100% offline functionality with zero dependency on network services for core features.

**OBJ-4:** Achieve pitch detection and reference tone generation meeting professional accuracy standards (detection ±1 cent, output ±1.5 cents).

### 1.4 Success Metrics

**SM-1:** Performance: Pitch detection latency under 100ms on 90% of supported devices.

**SM-2:** Stability: Crash rate below 0.5% of user sessions.

**SM-3:** Accuracy validation: Pass blind testing by professional musicians with 95%+ accuracy recognition.

### 1.5 Vision Statement

To provide musicians worldwide with a reliable, accurate, and simple chromatic tuner that works flawlessly offline on mobile devices, eliminating barriers to proper instrument tuning regardless of skill level, location, or network availability.

### 1.6 Business Risks

**RI-1:** **MEDIUM** - Microphone hardware variability across Android devices may affect pitch detection consistency and require extensive device-specific testing.

**RI-2:** **LOW** - iOS and Android app store approval processes may delay release or require design modifications to meet platform guidelines.

**RI-3:** **MEDIUM** - User expectations shaped by competing applications may lead to feature requests beyond initial scope.

**RI-4:** **LOW** - JUCE framework updates or platform SDK changes may require code maintenance and testing cycles.

**RI-5:** **LOW** - Without monetization strategy, sustained development and support may require volunteer contributions or future business model changes.

**RI-6:** **HIGH** - Background audio restrictions on mobile platforms may limit functionality when application is not in foreground.

### 1.7 Business Assumptions and Dependencies

**AS-1:** Target devices have functional microphones capable of capturing audio in the 32-4186 Hz frequency range with sufficient signal-to-noise ratio.

**AS-2:** Target devices have speakers or audio output capable of producing reference tones in the 261-523 Hz range.

**AS-3:** Users will grant microphone permissions required for pitch detection functionality.

**AS-4:** JUCE framework will continue to support iOS and Android platforms throughout development and initial release cycle.

**AS-5:** Development team has access to representative iOS and Android test devices spanning low-end to high-end hardware.

**AS-6:** Musicians understand basic music terminology (note names, cents, reference pitch concepts) or can learn through minimal in-app guidance.

**DE-1:** JUCE framework libraries and licensing terms remain compatible with free application distribution.

**DE-2:** iOS and Android platform APIs for audio input/output remain stable or provide backward compatibility.

**DE-3:** App store distribution platforms (Apple App Store, Google Play Store) remain available and accessible.

---

## 2. Scope and Limitations

### 2.1 Major Features

**MF-1: Chromatic Pitch Detection (Meter Mode)**
- Real-time microphone-based pitch detection across C1 (32.70 Hz) to C8 (4186.01 Hz)
- Visual display showing detected note name with octave number
- Analog-style tuning meter indicating pitch deviation in cents
- Flat/center/sharp visual indicators for quick tuning feedback
- Pure interval reference marks at -13.7 cents (pure major third) and +15.6 cents (pure minor third)
- 12-note equal temperament tuning system
- Detection accuracy: ±1 cent

**MF-2: Reference Tone Generation (Sound Mode)**
- Toggle activation of continuous reference tone output
- One-octave range: C4 (261.63 Hz) to C5 (523.25 Hz)
- Note selection via touchscreen interface
- Output accuracy: ±1.5 cents
- Immediate playback with no latency

**MF-3: Configurable Reference Pitch**
- A4 calibration adjustable from 410 Hz to 480 Hz
- 1 Hz increment adjustment control
- Default setting: 440 Hz (standard concert pitch)
- Persistent storage of user preference
- Real-time recalibration of all note frequencies when adjusted

**MF-4: Adaptive User Interface**
- Touch-optimized controls for mobile interaction
- Support for portrait and landscape device orientations
- Automatic layout adjustment for different screen sizes and aspect ratios
- Mode switching between Meter Mode and Sound Mode
- Clear visual hierarchy emphasizing tuning information

**MF-5: Offline Operation**
- Zero network connectivity requirements for all functionality
- No user account or authentication requirements
- No data transmission to external servers
- All processing performed on-device

### 2.2 Scope of Initial Release (Version 1.0)

**IR-1:** Chromatic pitch detection with real-time visual feedback (MF-1).

**IR-2:** Reference tone generation covering one octave (MF-2).

**IR-3:** A4 reference pitch calibration (MF-3).

**IR-4:** Landscape and portrait orientation support (MF-4).

**IR-5:** Offline-only operation with no network features (MF-5).

**IR-6:** Basic help screen explaining note names, cent deviation, and calibration concepts.

**IR-7:** Settings screen for reference pitch adjustment and application information.

**IR-8:** Single language support (English) for UI text and help content.

### 2.3 Scope of Subsequent Releases

**SR-1 (Version 1.1):** Alternative tuning systems (e.g., just intonation, Pythagorean, historical temperaments).

**SR-2 (Version 1.2):** Instrument-specific tuning presets (guitar, violin, brass instruments, etc.).

**SR-3 (Version 1.3):** Tuning history log showing sessions and detected pitch stability over time.

**SR-4 (Version 1.4):** Multiple language localizations based on user geography data from app stores.

**SR-5 (Version 2.0):** Dark mode theme option for low-light environments.

**SR-6 (Version 2.1):** Transposition feature for transposing instruments (Bb clarinet, F horn, etc.).

**SR-7 (Version 2.2):** Advanced visualization options (frequency spectrum display, waveform view).

**SR-8 (Version 2.3):** Noise reduction presets for different acoustic environments.

### 2.4 Limitations and Exclusions

**LE-1:** No background audio processing—application must remain in foreground for pitch detection and tone generation.

**LE-2:** No recording or audio file analysis—application only processes live microphone input.

**LE-3:** No social features, sharing capabilities, or user accounts.

**LE-4:** No cloud synchronization of settings or preferences across devices.

**LE-5:** No integration with external hardware MIDI devices or audio interfaces beyond standard mobile device audio I/O.

**LE-6:** No chord recognition or multi-note polyphonic detection—detects single fundamental pitch only.

**LE-7:** No spectral analysis display or advanced DSP visualization in initial release.

**LE-8:** No tuning for non-standard temperaments or microtuning systems in initial release.

**LE-9:** No automatic instrument detection or audio source identification.

**LE-10:** No haptic feedback for tuning status on devices with vibration capabilities.

**LE-11:** No accessibility features beyond platform-standard screen reader compatibility (future enhancement consideration).

**LE-12:** No tablet-specific UI optimizations—responsive design will adapt but not maximize tablet screen real estate.

---

## 3. Business Context

### 3.1 Stakeholder Profiles

**SP-1: Amateur Musicians (Primary Users)**
- **Description:** Hobbyists, students, and casual players of various instruments
- **Value proposition:** Free, simple tool for maintaining proper instrument tuning during practice
- **Key needs:** Easy-to-understand visual feedback, reliable accuracy, quick startup
- **Technical expertise:** Basic smartphone operation, minimal music theory knowledge
- **Usage patterns:** 2-5 minute sessions before practice, 2-4 times per week

**SP-2: Professional Musicians (Primary Users)**
- **Description:** Career musicians, music teachers, studio performers, orchestral players
- **Value proposition:** Professional-grade accuracy with configurable reference pitch for various performance contexts
- **Key needs:** Precise calibration options, fast response time, reference tone generation, pure interval markers
- **Technical expertise:** Advanced music theory knowledge, familiarity with cents and temperament concepts
- **Usage patterns:** Multiple daily sessions, pre-performance checks, teaching demonstrations

**SP-3: Music Educators (Secondary Users)**
- **Description:** Teachers using the application in lessons or ensemble rehearsals
- **Value proposition:** Free tool for demonstrating tuning concepts and providing consistent reference
- **Key needs:** Reliable performance, clear visual display visible to students, reference tone capabilities
- **Technical expertise:** Varies; music theory knowledge high, technical proficiency varies
- **Usage patterns:** Classroom demonstrations, ensemble tuning, student device recommendations

**SP-4: Development Team (Internal)**
- **Description:** Software engineers, designers, and audio DSP specialists building the application
- **Value proposition:** Clean codebase architecture leveraging JUCE for cross-platform efficiency
- **Key needs:** Clear requirements, testable acceptance criteria, manageable scope
- **Technical expertise:** JUCE framework, mobile development, audio signal processing
- **Responsibilities:** Implementation, testing, deployment, maintenance

**SP-5: Beta Testers (Supporting)**
- **Description:** Volunteer musicians testing pre-release versions
- **Value proposition:** Early access and influence on product direction
- **Key needs:** Clear feedback channels, acknowledgment of contributions
- **Technical expertise:** Varies widely
- **Usage patterns:** Intensive testing periods during beta phases

### 3.2 Project Priorities

| Priority Dimension | Constraint | Driver | Degree of Freedom |
|-------------------|-----------|--------|-------------------|
| **Features** | | ✓ | |
| **Schedule** | ✓ | | |
| **Budget** | ✓ | | |
| **Quality** | | ✓ | |

**Explanation:**

**Features (Driver):** Core functionality—accurate pitch detection, reference tone generation, and calibration—drives the project's value proposition. These features are non-negotiable and define minimum viable product.

**Schedule (Constraint):** 12-month target release window is constrained by volunteer developer availability and desire to launch before competing solutions saturate market.

**Budget (Constraint):** Free application model with no revenue stream constrains resources to volunteer time and minimal infrastructure costs. No budget for paid development, extensive testing devices, or marketing.

**Quality (Driver):** Accuracy, reliability, and performance directly impact user trust and adoption. Quality standards for pitch detection (±1 cent) and stability are essential drivers that cannot be compromised.

**Priority Guidance:**

- If schedule pressure increases, reduce features to core functionality (MF-1, MF-2, MF-3) and defer secondary features to subsequent releases.
- Quality standards for accuracy and performance must be maintained even if schedule extends.
- Budget constraints are absolute—no paid services or resources can be added.

### 3.3 Deployment Considerations

**DC-1: Platform Distribution**
- Deployment through Apple App Store (iOS) and Google Play Store (Android)
- Compliance with respective app store guidelines and review processes required
- Separate build configurations and signing certificates for each platform
- Initial release targeting iOS 13+ and Android 8.0+ for broad device coverage

**DC-2: Device Compatibility Testing**
- Minimum test coverage: 3 iOS devices (iPhone), 5 Android devices (varied manufacturers)
- Performance validation on low-end devices from target OS versions
- Microphone quality assessment across device spectrum
- Screen size and orientation testing for responsive UI validation

**DC-3: Audio Permissions**
- Microphone access permission requests with clear usage explanations
- Graceful handling of permission denial with user guidance
- No audio recording or storage—clarify privacy approach in permission dialogs

**DC-4: Update Strategy**
- Semantic versioning (MAJOR.MINOR.PATCH) for release identification
- Bug fixes deployed as patch updates within 2 weeks of discovery
- Feature additions scheduled as minor version updates quarterly
- Platform SDK compatibility maintained through framework updates

**DC-5: User Support**
- In-app help documentation for basic usage and concepts
- Contact information for bug reports and feature requests
- App store ratings monitoring for issue identification
- No real-time support infrastructure (email-based support only)

**DC-6: Privacy and Data Handling**
- No user data collection beyond platform analytics (downloads, crashes)
- No personal information storage or transmission
- Local-only storage of user preferences (reference pitch setting)
- Privacy policy documentation for app store compliance

**DC-7: Performance Monitoring**
- Crash reporting integration for stability tracking (platform-provided tools)
- No custom analytics or telemetry beyond app store standard metrics
- Performance regression testing in CI/CD pipeline for each release