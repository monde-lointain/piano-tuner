# Test Plan: SimpleTuner

## 1. Introduction

### 1.1 Purpose
This test plan defines the comprehensive testing strategy for SimpleTuner to ensure it meets all functional requirements, performance standards, and quality attributes specified in the requirements documentation.

### 1.2 Scope
Testing covers all application functionality across desktop (unit testing) and mobile (iOS/Android) platforms, including:

**Desktop Testing (Unit/Algorithm Validation):**
- Pitch detection algorithm accuracy (autocorrelation, NSDF, frequency extraction)
- Tone generation algorithm accuracy (sine synthesis, frequency calculation)
- Frequency calculation correctness (equal temperament, cent deviation)
- Configuration management logic (reference pitch storage/retrieval)
- Automated execution in CI/CD pipeline

**Mobile Device Testing (Integration/System/Acceptance):**
- Pitch detection and display (Meter Mode) with real audio hardware
- Reference tone generation (Sound Mode) through device speakers
- User interface and orientation handling
- Audio input/output management with platform audio systems
- Data persistence (UserDefaults, SharedPreferences)
- Cross-platform compatibility (iOS and Android)
- Performance, usability, and environmental testing

**Test Strategy:** Desktop unit tests execute first, gating mobile builds in CI/CD. Mobile testing proceeds only after desktop tests pass, ensuring core algorithm correctness before platform-specific integration testing.

### 1.3 Test Objectives
- Verify all functional requirements are correctly implemented
- Validate pitch detection accuracy meets ±1 cent specification
- Confirm tone generation accuracy within ±1.5 cents
- Ensure performance requirements (latency, CPU usage, memory)
- Validate usability across target user classes
- Confirm reliability and stability under extended use
- Verify cross-platform consistency

### 1.4 Test Environment
**Desktop (Unit Testing):**
- Platforms: macOS 11+, Ubuntu 20.04+, Windows 10+ (primary: developer workstations)
- Build System: CMake 3.20+
- Compiler: Clang 12+, GCC 10+, MSVC 2019+
- Test Framework: Google Test (lightweight C++ unit test framework)
- Execution: Local development machines, CI/CD runners (GitHub Actions, Jenkins, etc.)
- Purpose: Algorithm validation, regression prevention, rapid iteration

**iOS:**
- Devices: iPhone SE (2nd gen), iPhone 12, iPhone 14 Pro
- OS Versions: iOS 13.0, 15.0, 16.0, 17.0
- Development: Xcode 13+, macOS Monterey+

**Android:**
- Devices: Budget (2GB RAM), mid-range, flagship from varied manufacturers (Samsung, Google, Xiaomi)
- OS Versions: Android 8.0 (API 26), 10.0, 12.0, 14.0
- Development: Android Studio with NDK r21+

**Audio Test Equipment:**
- Professional audio interface for signal injection
- Calibrated reference frequency generator
- High-speed camera for latency measurement
- Sound level meter
- Acoustic test chamber (for noise testing)

### 1.5 Desktop Testing Strategy

**Rationale:**
Desktop-based unit testing enables rapid algorithm validation without mobile device deployment overhead. Unit tests execute in seconds locally and in CI/CD, providing immediate feedback on core algorithm correctness before time-intensive mobile builds.

**Scope of Desktop Testing:**
- **IN SCOPE:** Algorithm unit tests for pitch detection, tone generation, frequency calculations, configuration logic
- **OUT OF SCOPE:** UI testing, real audio I/O, platform-specific integration, performance/latency measurement

**Desktop Test Infrastructure:**
- **Minimal test runner:** Command-line executable, not comprehensive test harness
- **Unit tests only:** Focused on algorithmic correctness, not integration or system testing
- **Mock platform services:** Stub implementations of audio I/O, storage, permissions
- **Fast execution:** Test suite completes in <60 seconds

**CI/CD Integration:**
- Desktop tests run on every commit (pre-merge requirement)
- Mobile builds only proceed if desktop tests pass
- Test failures block pull requests
- Coverage metrics tracked over time (target: ≥80% of shared library)

**Test Execution Order:**
1. **Desktop unit tests** (Phase 0): Validate core algorithms
2. **iOS integration tests** (Phase 1): Verify iOS platform integration (if Phase 0 passes)
3. **Android integration tests** (Phase 2): Verify Android platform integration (if Phase 0 passes)
4. **System/Acceptance tests** (Phase 3): Comprehensive device testing (if Phases 0-2 pass)

---

## 2. Unit Testing

### 2.0 Desktop Unit Test Execution

**All unit tests described in Section 2 shall execute on desktop platforms via the command-line test runner before mobile device testing.**

**Desktop Test Execution:**
- **Build System:** CMake-based desktop executable
- **Platform:** macOS, Linux, Windows (developer workstations + CI/CD)
- **Mock Dependencies:**
  - `MockAudioInput`: Injects synthetic test signals with known frequencies
  - `MockAudioOutput`: Captures generated audio for verification
  - `MockConfigStorage`: In-memory preference storage for test isolation
  - `MockPermissions`: Auto-granted permissions for test environment
- **Test Assertions:** Standard C++ unit test framework (Google Test)
- **Coverage Target:** ≥80% of shared library code

**Mobile Unit Test Execution (Secondary):**
- iOS: XCTest framework on physical devices/simulators (after desktop tests pass)
- Android: JUnit + Android Instrumentation on emulators/devices (after desktop tests pass)
- Purpose: Verify platform-specific integrations, not re-test algorithms

**Execution Priority:**
1. Desktop tests execute first (seconds)
2. Mobile tests execute second (minutes)
3. Mobile builds only if desktop tests pass

### 2.1 Pitch Detection Algorithm Tests

**Test Module:** PitchDetector

**UT-PD-001: Normalized Square Difference Function (NSDF) Calculation**
- **Objective:** Verify NSDF correctly computed for autocorrelation analysis
- **Method:** Provide known test signal, verify NSDF output matches expected autocorrelation result
- **Pass Criteria:** NSDF values accurate within 0.01%

**UT-PD-002: Fundamental Frequency Extraction**
- **Objective:** Validate fundamental frequency identification from autocorrelation peaks
- **Method:** Generate synthetic audio with known fundamental (100-4000 Hz range)
- **Pass Criteria:** Detected frequency within ±0.5 Hz of input across frequency range

**UT-PD-003: Harmonic Rejection**
- **Objective:** Ensure algorithm distinguishes fundamental from harmonics
- **Method:** Input complex waveform with strong harmonics, verify fundamental correctly identified
- **Pass Criteria:** Fundamental identified correctly; harmonics not reported as fundamental

**UT-PD-004: Note Mapping Calculation**
- **Objective:** Verify frequency-to-note conversion accuracy
- **Method:** Test known frequencies map to correct note names and octaves
- **Pass Criteria:** All 88 piano keys (A0-C8) map correctly

**UT-PD-005: Cent Deviation Calculation**
- **Objective:** Validate cent calculation formula implementation
- **Method:** Compare calculated cents against mathematical expectation for various frequency pairs
- **Pass Criteria:** Cent values accurate within ±0.1 cents

**UT-PD-006: Confidence Scoring**
- **Objective:** Verify detection confidence calculation
- **Method:** Test clear signal (high confidence) vs. noisy signal (low confidence)
- **Pass Criteria:** Confidence metric correlates with signal quality

**UT-PD-007: Low Signal Rejection**
- **Objective:** Confirm signals below -40 dBFS threshold rejected
- **Method:** Input signals at various levels (-50 to -30 dBFS)
- **Pass Criteria:** Signals < -40 dBFS trigger "no signal" state

### 2.2 Tone Generation Tests

**Test Module:** ToneGenerator

**UT-TG-001: Frequency Calculation from Reference**
- **Objective:** Verify target frequency calculation using equal temperament formula
- **Method:** Test all 13 notes (C4-C5) with various reference pitches (410-480 Hz)
- **Pass Criteria:** Calculated frequencies match mathematical expectation within 0.01 Hz

**UT-TG-002: Sine Wave Synthesis**
- **Objective:** Validate pure sine wave generation
- **Method:** Analyze generated waveform via FFT for harmonic content
- **Pass Criteria:** Fundamental at target frequency, harmonics < -60 dB

**UT-TG-003: Phase Accumulator Continuity**
- **Objective:** Ensure phase continuity across buffer boundaries
- **Method:** Generate multiple buffers, verify no discontinuities
- **Pass Criteria:** No phase jumps > 0.1 radians between buffers

**UT-TG-004: Amplitude Stability**
- **Objective:** Confirm constant amplitude during generation
- **Method:** Measure peak amplitude over 10-second generation
- **Pass Criteria:** Amplitude variation < ±0.5 dB

**UT-TG-005: Fade Envelope Application**
- **Objective:** Verify fade-in/fade-out prevents clicking
- **Method:** Analyze tone start/stop for transients
- **Pass Criteria:** No transient energy > -40 dB outside target frequency

### 2.3 Frequency Calculation Tests

**Test Module:** FrequencyCalculator

**UT-FC-001: Equal Temperament Formula**
- **Objective:** Validate 12-TET frequency calculation
- **Method:** Compare calculated frequencies against published standards (ISO 16:1975)
- **Pass Criteria:** All calculations match standard within 0.01 Hz

**UT-FC-002: Reference Pitch Variation**
- **Objective:** Verify correct scaling for non-440 Hz references
- **Method:** Calculate A4=442 Hz and A4=415 Hz frequency sets
- **Pass Criteria:** Frequency ratios maintained; absolute values correct

**UT-FC-003: Octave Relationships**
- **Objective:** Confirm octave doubling/halving correct
- **Method:** Verify C4→C5 doubling, C5→C4 halving
- **Pass Criteria:** Ratios exactly 2:1 and 1:2

### 2.4 Configuration Management Tests

**Test Module:** ConfigurationManager

**UT-CM-001: Reference Pitch Storage**
- **Objective:** Verify preference persistence
- **Method:** Set reference pitch, simulate app restart, verify restored
- **Pass Criteria:** Value persists exactly

**UT-CM-002: Reference Pitch Validation**
- **Objective:** Ensure range enforcement (410-480 Hz)
- **Method:** Attempt to set values outside range
- **Pass Criteria:** Out-of-range values rejected or clamped

**UT-CM-003: Default Value Initialization**
- **Objective:** Confirm 440 Hz default on first launch
- **Method:** Fresh install without stored preference
- **Pass Criteria:** Reference pitch initializes to 440 Hz

**UT-CM-004: Corrupted Data Handling**
- **Objective:** Verify graceful handling of corrupted storage
- **Method:** Inject invalid data into storage
- **Pass Criteria:** Falls back to default 440 Hz without crash

---

## 3. Integration Testing

### 3.1 Audio Pipeline Integration

**IT-AP-001: Microphone to Pitch Detection**
- **Objective:** Validate end-to-end audio input pipeline
- **Method:** Play test tones through speaker into device microphone
- **Pass Criteria:** Correct note detected with < ±1 cent error

**IT-AP-002: Tone Generation to Speaker**
- **Objective:** Verify audio output pipeline
- **Method:** Generate tone, measure output with calibrated microphone
- **Pass Criteria:** Output frequency within ±1.5 cents of target

**IT-AP-003: Audio Session Configuration**
- **Objective:** Confirm proper iOS/Android audio session setup
- **Method:** Monitor audio session state during mode switches
- **Pass Criteria:** Correct category/usage set for each mode

**IT-AP-004: Buffer Size Adaptation**
- **Objective:** Verify handling of platform-determined buffer sizes
- **Method:** Test on devices with varying buffer size capabilities
- **Pass Criteria:** Application functions correctly regardless of buffer size

### 3.2 UI to Audio Integration

**IT-UA-001: Mode Switch to Audio State**
- **Objective:** Verify mode changes correctly activate/deactivate audio
- **Method:** Switch Meter↔Sound modes, monitor audio processing state
- **Pass Criteria:** Pitch detection active only in Meter; tone generation only in Sound

**IT-UA-002: Reference Pitch UI to Calculation**
- **Objective:** Confirm UI changes propagate to audio calculations
- **Method:** Adjust reference pitch, verify immediate effect on detection/generation
- **Pass Criteria:** Frequencies update within 100 ms of UI change

**IT-UA-003: Note Selection to Tone Frequency**
- **Objective:** Validate note selection updates generated tone
- **Method:** Select each note, verify correct frequency output
- **Pass Criteria:** All 13 notes generate correct frequencies

**IT-UA-004: Toggle Control to Tone State**
- **Objective:** Confirm play/stop toggle controls tone generation
- **Method:** Press toggle, monitor audio output
- **Pass Criteria:** Tone starts within 10 ms of press; stops within 10 ms

### 3.3 JUCE Framework Integration

**IT-JF-001: Audio Device Manager Integration**
- **Objective:** Verify JUCE AudioDeviceManager correctly interfaces with app
- **Method:** Test initialization, callback registration, device enumeration
- **Pass Criteria:** Audio I/O functions correctly through JUCE abstraction

**IT-JF-002: Autocorrelation Implementation**
- **Objective:** Validate autocorrelation computation accuracy
- **Method:** Process test signals, verify autocorrelation output matches expected values
- **Pass Criteria:** Autocorrelation results accurate within 0.01%

**IT-JF-003: Component Hierarchy Integration**
- **Objective:** Confirm GUI components render and respond correctly
- **Method:** Test touch events, repaints, layout changes
- **Pass Criteria:** All UI interactions function smoothly

### 3.4 Platform Integration

**IT-PF-001: iOS Permission System**
- **Objective:** Verify microphone permission request and handling
- **Method:** Test permission states (not determined, granted, denied)
- **Pass Criteria:** App responds appropriately to each state

**IT-PF-002: Android Permission System**
- **Objective:** Validate runtime permission flow
- **Method:** Test permission request, grant, denial, settings link
- **Pass Criteria:** Permission handled per Android guidelines

**IT-PF-003: iOS UserDefaults Integration**
- **Objective:** Confirm preference persistence on iOS
- **Method:** Write/read preferences, verify across app restarts
- **Pass Criteria:** Preferences persist reliably

**IT-PF-004: Android SharedPreferences Integration**
- **Objective:** Validate preference storage on Android
- **Method:** Write/read preferences, verify persistence
- **Pass Criteria:** Preferences persist reliably

### 3.5 Orientation Integration

**IT-OR-001: Orientation Change with Audio**
- **Objective:** Verify audio continues during orientation changes
- **Method:** Rotate device during pitch detection and tone generation
- **Pass Criteria:** No audio interruption; UI redraws correctly

**IT-OR-002: Layout Recalculation**
- **Objective:** Validate responsive layout across orientations
- **Method:** Switch portrait↔landscape, verify all elements visible and functional
- **Pass Criteria:** No clipping, overlap, or inaccessible controls

---

## 4. System Testing

### 4.1 Functional Testing

**ST-FN-001: Meter Mode Complete Workflow**
- **Objective:** Validate UC-001 end-to-end
- **Method:** Follow use case basic flow with real instrument
- **Pass Criteria:** User successfully tunes instrument using app

**ST-FN-002: Sound Mode Complete Workflow**
- **Objective:** Validate UC-002 end-to-end
- **Method:** Follow use case basic flow, select notes, play tones
- **Pass Criteria:** All reference tones generated accurately

**ST-FN-003: Reference Pitch Calibration Workflow**
- **Objective:** Validate UC-003 end-to-end
- **Method:** Adjust reference pitch, verify effect on both modes
- **Pass Criteria:** Settings persist; calculations update correctly

**ST-FN-004: Mode Switching**
- **Objective:** Validate UC-004
- **Method:** Switch between modes repeatedly
- **Pass Criteria:** Smooth transitions; audio states correct

**ST-FN-005: Orientation Handling**
- **Objective:** Validate UC-008
- **Method:** Use app in both orientations, perform all functions
- **Pass Criteria:** Full functionality in portrait and landscape

**ST-FN-006: Help Documentation Access**
- **Objective:** Validate UC-007
- **Method:** Access help, verify content comprehensibility
- **Pass Criteria:** Help accessible; content addresses user questions

### 4.2 Performance Testing

**ST-PF-001: Pitch Detection Latency**
- **Objective:** Verify latency ≤100 ms on 90% of devices
- **Method:** High-speed video analysis of input signal to display update
- **Pass Criteria:** Latency ≤100 ms on 9/10 test devices
- **Note:** 4096-sample buffer (93ms @ 44.1kHz) required for C1 detection accuracy

**ST-PF-002: Tone Generation Latency**
- **Objective:** Confirm tone starts within 10 ms
- **Method:** Measure time from button press to audio output
- **Pass Criteria:** Latency ≤10 ms on all devices

**ST-PF-003: Display Update Rate**
- **Objective:** Verify refresh rate ≥20 Hz
- **Method:** High-speed camera capture of display updates
- **Pass Criteria:** 95%+ of updates occur within 50 ms intervals

**ST-PF-004: CPU Utilization**
- **Objective:** Confirm CPU usage ≤15% (Meter) / ≤5% (Sound)
- **Method:** Profile CPU usage over 5-minute sessions
- **Pass Criteria:** Average CPU within limits; peaks ≤25%

**ST-PF-005: Memory Footprint**
- **Objective:** Verify memory usage ≤50 MB
- **Method:** Monitor peak resident memory over 30-minute session
- **Pass Criteria:** Peak memory ≤50 MB; no leaks (growth <1 MB/30 min)

**ST-PF-006: Battery Consumption**
- **Objective:** Ensure acceptable power usage
- **Method:** Monitor device temperature increase
- **Pass Criteria:** Temperature increase ≤3°C above baseline

**ST-PF-007: Audio Buffer Underrun Rate**
- **Objective:** Verify glitch rate <0.1%
- **Method:** Monitor audio callback performance over 30 minutes
- **Pass Criteria:** Underruns <18 per 30 minutes

**ST-PF-008: Application Launch Time**
- **Objective:** Confirm launch within 2 seconds
- **Method:** Measure cold launch time on minimum-spec devices
- **Pass Criteria:** 95%+ of launches ≤2 seconds

**ST-PF-009: Orientation Change Performance**
- **Objective:** Verify transition ≤200 ms
- **Method:** Time orientation change to completed redraw
- **Pass Criteria:** 100% of transitions ≤200 ms

### 4.3 Accuracy Testing

**ST-AC-001: Pitch Detection Accuracy**
- **Objective:** Verify detection accuracy ±1 cent
- **Method:** Input calibrated test tones across frequency range (40+ dB SNR)
- **Test Points:** C1, C2, A2, A3, A4, A5, A6, C7, C8 (key octaves)
- **Pass Criteria:** 95%+ of detections within ±1 cent

**ST-AC-002: Tone Generation Accuracy**
- **Objective:** Confirm output accuracy ±1.5 cents
- **Method:** Measure all 13 reference tones with calibrated frequency counter
- **Pass Criteria:** 100% of tones within ±1.5 cents

**ST-AC-003: Reference Pitch Calculation Accuracy**
- **Objective:** Verify frequency calculations across reference pitch range
- **Method:** Test reference pitches (410, 420, 440, 442, 460, 480 Hz)
- **Pass Criteria:** All calculated frequencies accurate to 0.01 Hz

**ST-AC-004: Cent Deviation Display Accuracy**
- **Objective:** Confirm cent display matches calculated deviation
- **Method:** Compare displayed cents with mathematical expectation
- **Pass Criteria:** Display accurate to ±0.1 cents

### 4.4 Usability Testing

**ST-US-001: First-Time User Learnability**
- **Objective:** Verify users can tune instrument within 2 minutes
- **Method:** Observe 20 first-time users (mixed skill levels)
- **Pass Criteria:** 80%+ achieve successful tuning within 2 minutes

**ST-US-002: Visual Clarity**
- **Objective:** Confirm legibility from 30-100 cm
- **Method:** User study at various distances and lighting conditions
- **Pass Criteria:** 90%+ of users read tuning status at 1 meter

**ST-US-003: Touch Target Accessibility**
- **Objective:** Verify touch targets meet size guidelines
- **Method:** Measure all interactive elements
- **Pass Criteria:** 100% of targets ≥44 pt (iOS) / 48 dp (Android)

**ST-US-004: Mode Switch Efficiency**
- **Objective:** Confirm single-tap mode switching
- **Method:** Count interactions required
- **Pass Criteria:** Mode switch requires exactly 1 tap

**ST-US-005: Settings Access Efficiency**
- **Objective:** Verify settings accessible within 2 taps
- **Method:** Count interactions from main screen to settings
- **Pass Criteria:** Settings accessible in ≤2 taps

### 4.5 Reliability Testing

**ST-RL-001: Extended Session Stability**
- **Objective:** Verify 30+ minute operation without failure
- **Method:** Run continuous pitch detection for 30 minutes
- **Pass Criteria:** No crashes, freezes, or degradation

**ST-RL-002: Rapid Interaction Stability**
- **Objective:** Ensure stability under rapid user actions
- **Method:** Rapidly tap controls, switch modes, rotate device
- **Pass Criteria:** No crashes; predictable behavior

**ST-RL-003: Memory Leak Detection**
- **Objective:** Confirm no memory growth over time
- **Method:** Monitor memory over 1-hour session
- **Pass Criteria:** Memory growth <5 MB over 1 hour

**ST-RL-004: Background/Foreground Cycling**
- **Objective:** Verify reliable recovery from backgrounding
- **Method:** Background and foreground app 50 times
- **Pass Criteria:** ≥99% successful audio reinitialization

**ST-RL-005: Orientation Change Stability**
- **Objective:** Ensure stability during orientation changes
- **Method:** Rotate device repeatedly during audio processing
- **Pass Criteria:** No crashes, audio continuity maintained

**ST-RL-006: Audio Interruption Handling**
- **Objective:** Verify graceful interruption handling
- **Method:** Simulate phone calls, alarms, other app audio
- **Pass Criteria:** App pauses appropriately; resumes correctly

### 4.6 Compatibility Testing

**ST-CP-001: iOS Device Compatibility**
- **Objective:** Verify functionality across iOS device range
- **Method:** Test on iPhone SE (minimum spec) through iPhone 14 Pro
- **Pass Criteria:** All critical requirements met on all devices

**ST-CP-002: Android Device Compatibility**
- **Objective:** Validate across Android manufacturers
- **Method:** Test on Samsung, Google, Xiaomi, OnePlus devices
- **Pass Criteria:** Core functionality works on all devices

**ST-CP-003: iOS Version Compatibility**
- **Objective:** Confirm support for iOS 13.0+
- **Method:** Test on iOS 13, 15, 16, 17
- **Pass Criteria:** No functionality loss across OS versions

**ST-CP-004: Android Version Compatibility**
- **Objective:** Validate Android 8.0+ support
- **Method:** Test on Android 8, 10, 12, 14
- **Pass Criteria:** No functionality loss across OS versions

**ST-CP-005: Screen Size Compatibility**
- **Objective:** Verify responsive design across screen sizes
- **Method:** Test on 4.7" to 6.8" displays
- **Pass Criteria:** UI scales correctly; no clipping or overlap

**ST-CP-006: Aspect Ratio Compatibility**
- **Objective:** Validate layout on various aspect ratios
- **Method:** Test 16:9, 18:9, 19.5:9, 20:9 displays
- **Pass Criteria:** Layout adapts correctly to all ratios

**ST-CP-007: External Audio Device Compatibility**
- **Objective:** Verify operation with headphones, Bluetooth
- **Method:** Test with wired headsets, Bluetooth headsets/speakers
- **Pass Criteria:** Audio routing works correctly; functionality preserved

### 4.7 Environmental Testing

**ST-EN-001: Quiet Environment Performance**
- **Objective:** Verify optimal performance in ideal conditions
- **Method:** Test in acoustic chamber (30-40 dB ambient)
- **Pass Criteria:** Detection accuracy optimal

**ST-EN-002: Moderate Noise Performance**
- **Objective:** Confirm functionality in typical practice environments
- **Method:** Test with 50-60 dB ambient noise
- **Pass Criteria:** Acceptable detection accuracy maintained

**ST-EN-003: High Noise Degradation**
- **Objective:** Validate graceful degradation in noisy environments
- **Method:** Test with 60-70 dB ambient noise
- **Pass Criteria:** Unstable readings or "no signal" rather than false detections

**ST-EN-004: Varied Lighting Conditions**
- **Objective:** Ensure display legibility in diverse lighting
- **Method:** Test in dim (100 lux), indoor (300-500 lux), outdoor (10000+ lux)
- **Pass Criteria:** Display readable in all conditions

---

## 5. Acceptance Testing

### 5.1 User Acceptance Testing (UAT)

**AT-UA-001: Amateur Musician Workflow**
- **Participants:** 10 amateur musicians (hobbyists, students)
- **Scenario:** Tune guitar using Meter Mode
- **Success Criteria:** 
  - 80%+ successfully tune within 5 minutes
  - 90%+ report interface is clear and easy to understand
  - 80%+ report they would use app for regular tuning

**AT-UA-002: Professional Musician Workflow**
- **Participants:** 10 professional musicians (varied instruments)
- **Scenario:** Use all features including calibration, reference tones
- **Success Criteria:**
  - 100% successfully calibrate reference pitch
  - 90%+ report accuracy meets professional standards
  - 80%+ report they would recommend to colleagues

**AT-UA-003: Music Educator Workflow**
- **Participants:** 5 music educators
- **Scenario:** Use for teaching demonstration
- **Success Criteria:**
  - 100% successfully demonstrate tuning concepts
  - 80%+ report display visible to students
  - 80%+ report they would use in classroom

### 5.2 Functional Acceptance

**AT-FN-001: All Critical Requirements Implemented**
- **Objective:** Verify all CRITICAL priority requirements delivered
- **Method:** Requirements traceability matrix review
- **Pass Criteria:** 100% of CRITICAL requirements implemented and tested

**AT-FN-002: Pitch Detection Range Coverage**
- **Objective:** Confirm C1 (32.70 Hz) to C8 (4186.01 Hz) coverage
- **Method:** Test boundary frequencies and mid-range
- **Pass Criteria:** Detection works across entire specified range

**AT-FN-003: Reference Tone Range Coverage**
- **Objective:** Verify C4-C5 tone generation
- **Method:** Generate all 13 reference tones
- **Pass Criteria:** All tones generated accurately

**AT-FN-004: Reference Pitch Range Coverage**
- **Objective:** Confirm 410-480 Hz calibration range
- **Method:** Set reference pitch to boundary values
- **Pass Criteria:** All values in range accepted; calculations correct

### 5.3 Performance Acceptance

**AT-PF-001: Latency Requirements Met**
- **Objective:** Confirm latency specifications achieved
- **Method:** Statistical analysis of latency measurements
- **Pass Criteria:**
  - Pitch detection ≤100 ms on 90%+ devices
  - Tone generation ≤10 ms on 100% devices

**AT-PF-002: Resource Usage Acceptable**
- **Objective:** Verify CPU and memory within limits
- **Method:** Performance profiling across device spectrum
- **Pass Criteria:**
  - CPU ≤15% (Meter), ≤5% (Sound)
  - Memory ≤50 MB peak
  - Temperature increase ≤3°C

**AT-PF-003: Stability Requirements Met**
- **Objective:** Confirm crash rate <0.5%
- **Method:** Aggregate crash data from beta testing
- **Pass Criteria:** Crash rate <0.5% of sessions

### 5.4 Accuracy Acceptance

**AT-AC-001: Pitch Detection Accuracy Specification**
- **Objective:** Verify ±1 cent detection accuracy
- **Method:** Statistical analysis of calibrated test tone detections
- **Pass Criteria:** 95%+ detections within ±1 cent (40+ dB SNR)

**AT-AC-002: Tone Generation Accuracy Specification**
- **Objective:** Confirm ±1.5 cent output accuracy
- **Method:** Precision frequency measurements of all tones
- **Pass Criteria:** 100% of tones within ±1.5 cents

**AT-AC-003: Professional Musician Accuracy Assessment**
- **Objective:** Validate accuracy meets professional standards
- **Method:** Blind testing by 10 professional musicians
- **Pass Criteria:** 90%+ recognize accuracy as professional-grade

### 5.5 Platform Acceptance

**AT-PL-001: iOS App Store Readiness**
- **Objective:** Verify compliance with App Store Review Guidelines
- **Method:** Pre-submission checklist review
- **Pass Criteria:** All guidelines met; no violations identified

**AT-PL-002: Android Play Store Readiness**
- **Objective:** Confirm Google Play Developer Policy compliance
- **Method:** Pre-submission policy review
- **Pass Criteria:** All policies met; no violations identified

**AT-PL-003: Installation Size Requirement**
- **Objective:** Verify installation package ≤25 MB
- **Method:** Measure .ipa and .apk file sizes
- **Pass Criteria:** iOS and Android packages both ≤25 MB

### 5.6 Offline Operation Acceptance

**AT-OF-001: Network Independence**
- **Objective:** Confirm 100% offline functionality
- **Method:** Test all features in airplane mode
- **Pass Criteria:** All features functional without network

**AT-OF-002: First Launch Without Network**
- **Objective:** Verify offline first-time use
- **Method:** Fresh install and launch in airplane mode
- **Pass Criteria:** App initializes and functions normally

---

## 6. Test Execution Strategy

### 6.1 Test Phases

**Phase 0: Desktop Unit Testing (Continuous, Weeks 1-12)**
- Developers write unit tests alongside feature implementation
- Tests execute locally before committing code
- CI/CD runs full desktop test suite on every commit
- Target: ≥80% code coverage of shared library
- Execution time: <60 seconds
- **Entry Criteria:** Feature code complete
- **Exit Criteria:** All desktop unit tests passing, coverage target met
- **Gating:** Blocks merge to main branch if tests fail

**Phase 1: Mobile Integration Testing (Weeks 3-4)**
- QA team executes integration test suite on mobile devices
- Focus on audio pipeline and platform integration
- Automated where feasible; manual for hardware interaction
- **Entry Criteria:** Desktop unit tests passing, mobile build compiles
- **Exit Criteria:** Audio I/O functional, platform integrations working
- **Dependencies:** Requires Phase 0 passing

**Phase 2: System Testing (Weeks 5-7)**
- Comprehensive functional, performance, compatibility testing on mobile devices
- Multiple device testing in parallel
- Accuracy testing with calibrated equipment
- **Entry Criteria:** Integration tests passing, all features complete
- **Exit Criteria:** All critical/high priority test cases passing
- **Dependencies:** Requires Phases 0-1 passing

**Phase 3: Beta Testing (Weeks 8-10)**
- Distribute to 50-100 volunteer musicians
- Collect usage data, crash reports, feedback
- Address critical issues before release
- **Entry Criteria:** System testing complete, build stable
- **Exit Criteria:** <0.5% crash rate, user satisfaction >80%
- **Dependencies:** Requires Phases 0-2 passing

**Phase 4: Acceptance Testing (Week 11)**
- Final UAT with representative users
- Final accuracy validation
- App store compliance verification
- **Entry Criteria:** Beta testing complete, all critical issues resolved
- **Exit Criteria:** Acceptance criteria met, app store compliance verified
- **Dependencies:** Requires Phases 0-3 passing

**Phase 5: Release (Week 12)**
- App store submission
- Post-release monitoring
- **Entry Criteria:** Acceptance testing complete, release checklist verified
- **Dependencies:** Requires all previous phases passing

### 6.2 Entry and Exit Criteria

**Entry Criteria (Mobile Testing Phases):**
- **Desktop unit tests passing** (≥80% coverage, all tests green)
- Feature complete per requirements
- Mobile builds compiling successfully (iOS + Android)
- Build stable (no critical crashes in desktop tests)
- Test environment configured
- Test devices available

**Entry Criteria (Desktop Unit Testing Phase):**
- Feature code implemented
- Test cases written for new functionality
- Local build successful

**Exit Criteria (Release Readiness):**
- Desktop unit tests: 100% passing, ≥80% coverage
- All CRITICAL and HIGH priority mobile tests passing
- No open critical or high-severity defects
- Performance requirements met
- Acceptance criteria satisfied
- App store compliance verified

### 6.3 Defect Management

**Severity Levels:**
- **Critical:** App crashes, data loss, core functionality broken
- **High:** Feature doesn't work as specified, major usability issue
- **Medium:** Minor functionality issue, workaround exists
- **Low:** Cosmetic issue, minor inconvenience

**Resolution Timelines:**
- Critical: Fix within 24 hours
- High: Fix within 1 week
- Medium: Fix in next release
- Low: Backlog for future consideration

### 6.4 Test Automation

**Automated Tests:**
- **Desktop unit tests:** 100% automated via CMake + CI/CD
  - Pitch detection algorithm tests
  - Tone generation algorithm tests
  - Frequency calculation tests
  - Configuration management tests
  - Executes in <60 seconds
  - Runs on every commit
- **Mobile unit tests:** Partial automation (XCTest, JUnit)
- **Integration tests:** Partial automation (audio testing requires hardware)
- **Performance monitoring:** Automated profiling
- **Crash reporting:** Automated collection via platform tools

**Manual Tests:**
- Usability testing
- Accuracy measurement with calibrated equipment
- Cross-device compatibility verification
- User acceptance testing

---

## 7. Test Deliverables

1. **Test Case Specifications** - Detailed test procedures for all test IDs
2. **Test Execution Reports** - Results from each test phase
3. **Defect Reports** - Tracking of all identified issues
4. **Performance Benchmarks** - Latency, CPU, memory measurements
5. **Accuracy Validation Report** - Calibrated measurement results
6. **Compatibility Matrix** - Device/OS test coverage
7. **User Acceptance Report** - UAT feedback and results
8. **Final Test Summary Report** - Overall quality assessment
9. **Release Recommendation** - Go/no-go decision documentation

---

## 8. Risks and Mitigation

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| Insufficient test devices | Medium | High | Prioritize most popular models; leverage beta testers |
| Calibrated audio equipment unavailable | Low | High | Partner with audio testing lab; use professional reference tuner |
| Android device fragmentation | High | Medium | Focus on top manufacturers; extensive beta testing |
| Platform OS update breaks functionality | Medium | High | Monitor beta OS releases; test preemptively |
| Microphone quality varies significantly | High | Medium | Design robust algorithms; document device limitations |
| Limited volunteer beta testers | Medium | Medium | Recruit from music communities; incentivize participation |

---

## 9. Test Schedule

| Phase | Duration | Activities |
|-------|----------|------------|
| **Desktop Unit Testing** | **Weeks 0-12 (Continuous)** | **Developer-driven unit tests, CI/CD automation** |
| Test Planning | Week 0 | Finalize test plan, prepare environment |
| Mobile Integration Testing | Weeks 3-4 | QA integration test execution (after desktop tests pass) |
| System Testing | Weeks 5-7 | Comprehensive mobile device test execution |
| Beta Testing | Weeks 8-10 | Public beta, feedback collection |
| Acceptance Testing | Week 11 | UAT, final validation |
| Release | Week 12 | App store submission |

**Note:** Desktop unit testing runs continuously throughout all phases. Mobile testing phases only proceed after desktop tests pass in CI/CD.

---

## 10. Resources

**Personnel:**
- Test Lead (1)
- QA Engineers (2)
- Audio Testing Specialist (1, consultant)
- Beta Program Coordinator (1)
- Developers (for unit testing, bug fixes)

**Equipment:**
- iOS test devices (3)
- Android test devices (5)
- Audio interface and frequency generator
- High-speed camera
- Sound level meter
- Acoustic test environment

**Software:**
- **Desktop testing:**
  - CMake 3.20+ (build system)
  - Google Test (C++ unit test framework)
  - CI/CD platform (GitHub Actions, Jenkins, etc.)
  - Code coverage tools (gcov, lcov, or similar)
- Xcode with testing tools
- Android Studio with testing tools
- Audio analysis software
- Defect tracking system
- Test management tool