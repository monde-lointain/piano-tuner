# Software Requirements Specification

## SimpleTuner

## 1. Introduction

### 1.1 Purpose

This Software Requirements Specification (SRS) document provides a comprehensive technical description of the functional and non-functional requirements for SimpleTuner. This document is intended for:

- **Development team members** implementing the application using the JUCE framework
- **Quality assurance engineers** developing test plans and validation procedures
- **Project stakeholders** evaluating technical feasibility and requirement completeness
- **Third-party reviewers** assessing compliance with app store guidelines
- **Future maintainers** understanding system architecture and design rationale

This SRS defines the software requirements necessary to deliver a production-ready chromatic tuner application that meets the business objectives outlined in the Vision and Scope Document. It establishes the technical foundation for development activities, test case creation, and acceptance criteria validation.

The specification focuses exclusively on software requirements and does not address project management activities, deployment logistics, or marketing considerations except where they directly impact software design decisions.

### 1.2 Document Conventions

This document adheres to the following conventions:

**Requirement Identifiers:**
- Functional requirements use the prefix **FR-** followed by a hierarchical numbering scheme (e.g., FR-1.1.1)
- Non-functional requirements use the prefix **NFR-** followed by category and number (e.g., NFR-PERF-1)
- User interface requirements use the prefix **UI-** followed by sequential numbering (e.g., UI-1)
- Data requirements use the prefix **DR-** followed by sequential numbering (e.g., DR-1)

**Priority Levels:**
All requirements are classified using the following priority scheme:
- **CRITICAL:** Essential for minimum viable product; must be implemented in Version 1.0
- **HIGH:** Important functionality that significantly impacts user experience; should be implemented in Version 1.0 unless schedule constraints require deferral
- **MEDIUM:** Desirable functionality that enhances user experience; may be deferred to subsequent releases if necessary
- **LOW:** Optional enhancements that provide incremental value; planned for future releases

**Terminology:**
- **Cent:** A logarithmic unit of musical interval measurement; 100 cents equals one semitone
- **Chromatic:** Including all twelve pitches of the equal-tempered scale
- **Equal temperament:** A tuning system dividing the octave into twelve equal semitones
- **Fundamental frequency:** The lowest frequency component of a periodic waveform; the perceived pitch
- **JUCE:** Jules' Utility Class Extensions, a C++ framework for cross-platform audio application development
- **Pitch detection:** The process of identifying the fundamental frequency of an audio signal
- **Reference pitch (A4):** The standard tuning reference, conventionally 440 Hz
- **Semitone:** The interval between adjacent notes in the twelve-tone equal-tempered scale

**Visual Conventions:**
- Technical specifications and exact values appear in `monospace font`
- User interface element names appear in **bold text**
- Referenced document sections appear in *italics*
- Mathematical formulas and frequency values use standard scientific notation

**Measurement Units:**
- Frequency: Hertz (Hz)
- Time: Milliseconds (ms) or seconds (s)
- Pitch deviation: Cents
- File size: Megabytes (MB)

### 1.3 Project Scope

SimpleTuner provides musicians with a professional-grade, offline-capable tool for accurate instrument tuning through real-time pitch detection and reference tone generation. The application operates entirely on-device without network connectivity requirements, ensuring reliable functionality during practice sessions, rehearsals, and performances in any location.

**In Scope:**

The application delivers two primary operating modes accessible through a touchscreen interface:

1. **Meter Mode (Automatic Pitch Detection):**
   - Continuous microphone-based pitch detection analyzing audio input in real-time
   - Visual display of detected note name with octave designation (e.g., A4, C#3)
   - Analog-style tuning meter showing pitch deviation from target frequency measured in cents
   - Visual indicators communicating tuning status: flat (below target), center (in tune), sharp (above target)
   - Pure interval reference markers on the meter at -13.7 cents (pure major third) and +15.6 cents (pure minor third) to assist with historical temperament awareness
   - Detection coverage spanning seven octaves from C1 (32.70 Hz) to C8 (4186.01 Hz)
   - Detection accuracy meeting professional standards (±1 cent tolerance)

2. **Sound Mode (Reference Tone Generation):**
   - User-activated continuous reference tone output through device speakers
   - Toggle control enabling immediate tone activation and deactivation
   - One-octave note selection range from C4 (261.63 Hz) to C5 (523.25 Hz)
   - Note selection through intuitive touchscreen interface
   - Output accuracy meeting professional standards (±1.5 cents tolerance)
   - Zero-latency tone generation response to user interaction

3. **Configurable Reference Pitch:**
   - User-adjustable A4 calibration supporting range from 410 Hz to 480 Hz
   - Fine-grained adjustment in 1 Hz increments
   - Default setting of 440 Hz (international concert pitch standard)
   - Persistent storage of user preference across application sessions
   - Real-time recalculation of all note frequencies based on selected reference pitch

4. **Cross-Platform Mobile Operation:**
   - Native iOS application supporting iPhone devices with iOS 13 or later
   - Native Android application supporting devices with Android 8.0 or later
   - Unified codebase leveraging JUCE framework for consistent behavior across platforms
   - Touch-optimized user interface supporting both portrait and landscape orientations
   - Responsive layout adapting to various screen sizes and aspect ratios
   - Platform-appropriate visual design following iOS and Android interface guidelines

**Key Benefits:**

- **Offline Independence:** Complete functionality without network connectivity eliminates barriers in remote locations, during travel, or in venues with unreliable internet access
- **Professional Accuracy:** Pitch detection and tone generation meeting professional musician standards for rehearsal, performance, and teaching applications
- **Universal Accessibility:** Free distribution removes financial barriers for students, amateur musicians, and professionals in regions with limited access to commercial tuning solutions
- **Simplicity:** Focused feature set prioritizing core tuning functionality over complex options that can overwhelm casual users
- **Reliability:** Self-contained on-device processing eliminates dependencies on external services that may experience downtime or discontinuation

**Out of Scope:**

The following capabilities are explicitly excluded from Version 1.0 and may be considered for future releases:

- Alternative tuning systems (just intonation, Pythagorean tuning, historical temperaments beyond pure interval markers)
- Instrument-specific tuning presets or guided tuning sequences
- Background audio processing when application is not in foreground
- Audio recording, storage, or file-based analysis
- Polyphonic detection or chord recognition
- Integration with external MIDI devices or professional audio interfaces
- Social features, cloud synchronization, or user accounts
- Spectral analysis visualization beyond basic tuning meter
- Haptic feedback or advanced accessibility features
- Tablet-optimized layouts (responsive design will adapt but not maximize tablet screen usage)
- Multiple language localizations (English only in Version 1.0)
- Dark mode or alternative visual themes

This focused scope ensures delivery of a robust, reliable tuning solution within resource constraints while establishing a foundation for potential future enhancements based on user feedback and adoption patterns.

### 1.4 References

This Software Requirements Specification should be read in conjunction with the following documents:

**Project Documentation:**

1. **Vision and Scope Document - SimpleTuner**  
   Version 1.0, December 10, 2025  
   Defines business requirements, objectives, stakeholder profiles, and project scope boundaries

**Technical Standards and Specifications:**

2. **ISO 16:1975 - Acoustics - Standard Tuning Frequency (Standard Musical Pitch)**  
   International Organization for Standardization  
   Establishes A4 = 440 Hz as international standard reference pitch

3. **ANSI S1.1-1994 (R2004) - Acoustical Terminology**  
   American National Standards Institute  
   Defines standard terminology for acoustical measurements and pitch perception

4. **IEEE 754-2019 - Standard for Floating-Point Arithmetic**  
   Institute of Electrical and Electronics Engineers  
   Specifies floating-point computation standards relevant to audio signal processing

**Framework and Platform Documentation:**

5. **JUCE Framework Documentation**  
   Version 7.0 or later  
   Available at: https://juce.com/learn/documentation  
   Comprehensive reference for JUCE audio processing, DSP modules, and cross-platform UI components

6. **Apple App Store Review Guidelines**  
   Current version at time of submission  
   Available at: https://developer.apple.com/app-store/review/guidelines/  
   Platform requirements for iOS application approval and distribution

7. **Google Play Developer Policy Center**  
   Current version at time of submission  
   Available at: https://play.google.com/about/developer-content-policy/  
   Platform requirements for Android application approval and distribution

8. **iOS Human Interface Guidelines**  
   Current version at time of implementation  
   Available at: https://developer.apple.com/design/human-interface-guidelines/  
   Design principles and patterns for iOS applications

9. **Android Material Design Guidelines**  
   Current version at time of implementation  
   Available at: https://material.io/design  
   Design principles and patterns for Android applications

**Audio and Signal Processing References:**

10. **"A Smarter Way to Find Pitch" by Philip McLeod**
    Proceedings of the 2005 International Computer Music Conference (ICMC 2005)
    Reference for McLeod Pitch Period Method (PPM) using Normalized Square Difference Function (NSDF)

11. **"Music and Acoustics" by Philip M. Morse**
    Acoustical Society of America
    Foundation for equal temperament calculations and frequency relationships

**Regulatory and Compliance:**

12. **General Data Protection Regulation (GDPR)**  
    EU Regulation 2016/679  
    Privacy requirements applicable to European users (though minimal data collection limits applicability)

13. **California Consumer Privacy Act (CCPA)**  
    California Civil Code §1798.100 et seq.  
    Privacy requirements for California users (though minimal data collection limits applicability)

**Quality Standards:**

14. **ISO/IEC 25010:2011 - Systems and Software Quality Requirements and Evaluation (SQuaRE)**  
    International Organization for Standardization  
    Framework for software quality characteristics guiding non-functional requirements

**Acronyms and Abbreviations:**

- **API:** Application Programming Interface
- **CPU:** Central Processing Unit
- **DSP:** Digital Signal Processing
- **NSDF:** Normalized Square Difference Function
- **FPS:** Frames Per Second
- **GUI:** Graphical User Interface
- **Hz:** Hertz (cycles per second)
- **iOS:** iPhone Operating System (Apple mobile platform)
- **JUCE:** Jules' Utility Class Extensions
- **kHz:** Kilohertz (1000 Hz)
- **MB:** Megabyte
- **ms:** Millisecond
- **OS:** Operating System
- **RAM:** Random Access Memory
- **SDK:** Software Development Kit
- **SRS:** Software Requirements Specification
- **UI:** User Interface
- **UX:** User Experience

---

## 2. Overall Description

### 2.1 Product Perspective

SimpleTuner is a self-contained, standalone software product designed for iOS and Android mobile devices. It operates independently without reliance on external systems, network services, or companion applications.

#### 2.1.1 System Context

The application exists within the following system context:

**Mobile Device Platform:**
The application executes as a native mobile application within the iOS or Android operating system environment. It interfaces directly with platform-provided audio subsystems for microphone input and speaker output, leveraging the JUCE framework to abstract platform-specific audio API differences.

**Hardware Interfaces:**
- **Microphone:** Accesses device microphone through platform audio input APIs for pitch detection. The application processes raw audio buffers but does not record, store, or transmit captured audio.
- **Speaker/Audio Output:** Generates reference tones through platform audio output APIs. Synthesized audio is produced in real-time without intermediate file generation.
- **Touchscreen:** Receives user input through platform touch event handling for mode selection, note selection, and configuration adjustments.
- **Display:** Renders user interface and tuning visualization through platform graphics subsystems.
- **Device Storage:** Persists minimal user preferences (reference pitch calibration) using platform-provided local storage mechanisms.

**External System Independence:**
The application deliberately maintains no interfaces to:
- Network services or cloud platforms
- External databases or remote data stores
- Third-party authentication systems
- Social media or sharing platforms
- Analytics or telemetry services beyond platform-standard app store metrics
- Advertisement networks or monetization services
- External audio hardware beyond standard device I/O

**Application Store Distribution:**
While the application operates independently after installation, it is distributed through:
- Apple App Store (iOS): Subject to Apple's review process, sandboxing requirements, and distribution infrastructure
- Google Play Store (Android): Subject to Google's review process, platform security model, and distribution infrastructure

#### 2.1.2 Architectural Position

**Framework Architecture:**
The application is built upon the JUCE framework, which provides:
- Cross-platform audio I/O abstraction layer
- Digital signal processing utilities for autocorrelation and pitch analysis
- GUI component library with touch event handling
- Thread management for real-time audio processing
- Platform-specific code generation at build time

**Layered Architecture:**
```
┌─────────────────────────────────────────────────┐
│         User Interface Layer                    │
│  (Touch Events, Visual Display, Mode Control)   │
├─────────────────────────────────────────────────┤
│        Application Logic Layer                  │
│  (Pitch Detection, Tone Generation, Config)     │
├─────────────────────────────────────────────────┤
│            JUCE Framework Layer                 │
│  (Audio I/O, DSP, GUI, Platform Abstraction)    │
├─────────────────────────────────────────────────┤
│         Platform Native Layer                   │
│     (iOS: CoreAudio, UIKit / Android:           │
│      OpenSL ES, Android SDK)                    │
├─────────────────────────────────────────────────┤
│          Mobile Device Hardware                 │
│   (Microphone, Speaker, CPU, Display, Touch)    │
└─────────────────────────────────────────────────┘
```

**Processing Model:**
The application employs parallel processing streams:
- **Main UI Thread:** Handles touch events, display updates, and non-real-time operations
- **Audio Thread:** Processes incoming microphone data for pitch detection or generates outgoing reference tone synthesis with real-time constraints
- **Configuration Thread:** Manages persistent storage operations without blocking audio or UI responsiveness

#### 2.1.3 Product Position in Market

The application occupies a specific niche addressing gaps in existing tuner solutions:

**Differentiators:**
- **Offline-first design:** Unlike web-based tuners, functions without network connectivity
- **Professional accuracy with simplicity:** Balances precise measurement (±1 cent) with uncluttered interface suitable for both professionals and beginners
- **Free without monetization:** No advertisements, in-app purchases, or subscription models that may compromise user experience
- **Cross-platform consistency:** JUCE framework ensures identical behavior and interface across iOS and Android rather than divergent platform-specific implementations
- **Pure interval markers:** Educational feature showing historical temperament references uncommon in competing applications

**Constraints Relative to Competitors:**
- Limited to single-note monophonic detection (no chord recognition)
- No instrument-specific presets or guided tuning sequences
- Basic visual design compared to applications with extensive customization options
- Single language support (English only) in initial release

#### 2.1.4 Integration Requirements

**Platform Integration:**
The application integrates with platform capabilities through standard APIs:
- **Permission System:** Requests microphone access permission using platform-standard dialogs
- **Audio Session Management:** Configures audio routing, interruption handling, and hardware sample rate adaptation
- **Application Lifecycle:** Responds to foreground/background transitions, memory warnings, and system interruptions
- **Settings Storage:** Uses platform UserDefaults (iOS) or SharedPreferences (Android) for persisting reference pitch calibration
- **Screen Orientation:** Integrates with platform orientation change notifications for responsive layout

**No External Integration:**
The application explicitly avoids integration with:
- Cloud storage services
- Social media platforms
- External authentication providers
- Third-party analytics frameworks
- Remote configuration systems
- Content delivery networks

This isolation ensures offline functionality, minimizes privacy concerns, and reduces maintenance burden from third-party API changes.

### 2.2 User Classes and Characteristics

The application serves distinct user classes with varying needs, technical expertise, and usage patterns. Requirements prioritize the first two classes while accommodating the third.

#### 2.2.1 Amateur Musicians (Primary User Class)

**Profile:**
- Hobbyists, students, and casual instrument players
- Age range: 12-65+ years
- Musical experience: Beginner to intermediate
- Technical proficiency: Basic smartphone operation; may be unfamiliar with music theory terminology

**Characteristics:**
- **Primary need:** Simple, intuitive tool to verify instrument is "in tune" before practice
- **Usage frequency:** 2-5 minute sessions, 2-4 times per week before practice sessions
- **Context of use:** Home practice environment, typically quiet with minimal background noise
- **Decision drivers:** Visual clarity of tuning status (flat/center/sharp indicators), ease of understanding without extensive musical training
- **Tolerance for complexity:** Low; prefers application to "just work" without configuration

**Key Requirements:**
- Clear visual indication of tuning status without requiring cent value interpretation
- Automatic note detection without manual note selection
- Default settings appropriate for common use cases (440 Hz reference pitch)
- Immediate startup with minimal navigation
- Obvious mode switching between pitch detection and reference tone

**Representative Tasks:**
1. Open application and immediately see if guitar string is flat, sharp, or in tune
2. Play reference tone to match pitch by ear during tuning process
3. Verify instrument is tuned after making adjustments

**Accommodation Strategy:**
- Design user interface prioritizing visual tuning indicators over numeric cent displays
- Provide brief in-app help explaining note names and basic concepts
- Minimize configuration requirements; reasonable defaults for all settings
- Ensure consistent behavior across application launches without requiring setup

#### 2.2.2 Professional Musicians (Primary User Class)

**Profile:**
- Career musicians, music teachers, studio performers, orchestral players
- Age range: 18-70+ years
- Musical experience: Advanced to expert
- Technical proficiency: Varies; comfortable with music terminology (cents, temperament, calibration)

**Characteristics:**
- **Primary need:** Precise tuning reference with configurable calibration to match ensemble or performance context
- **Usage frequency:** Multiple daily sessions; pre-performance checks; teaching demonstrations
- **Context of use:** Variable acoustic environments including rehearsal spaces, concert halls, recording studios, teaching studios
- **Decision drivers:** Measurement accuracy, reference pitch configurability, pure interval awareness, response speed
- **Tolerance for complexity:** High; values advanced features like calibration adjustment and cent precision

**Key Requirements:**
- Detection accuracy meeting professional standards (±1 cent)
- Configurable A4 reference pitch to accommodate orchestral tuning (e.g., 442 Hz), historical performance (e.g., 415 Hz), or regional variations
- Cent value display for precise tuning adjustments
- Pure interval reference markers for awareness of temperament implications
- Fast response time for efficient tuning workflows
- Reference tone generation for teaching demonstrations or aural tuning

**Representative Tasks:**
1. Configure reference pitch to 442 Hz to match orchestra tuning standard
2. Use cent display to achieve precise unison with another instrument
3. Verify instrument tuning stability over extended rehearsal period
4. Generate reference tone during teaching to demonstrate target pitch
5. Check tuning between movements during performance

**Accommodation Strategy:**
- Provide reference pitch calibration with 1 Hz precision across practical range
- Display cent values prominently for users who interpret numerical deviation
- Include pure interval markers as educational feature for historical awareness
- Ensure pitch detection latency under 100ms for responsive professional use
- Maintain accuracy standards comparable to professional hardware tuners

#### 2.2.3 Music Educators (Secondary User Class)

**Profile:**
- Private teachers, ensemble directors, classroom music instructors
- Age range: 25-65+ years
- Musical experience: Advanced
- Technical proficiency: Varies; strong music theory knowledge, variable smartphone expertise

**Characteristics:**
- **Primary need:** Reliable demonstration tool for teaching tuning concepts and providing consistent reference
- **Usage frequency:** Daily during lessons, rehearsals, and classroom demonstrations
- **Context of use:** Teaching studios, classrooms, ensemble rehearsal spaces; may need visibility to multiple students
- **Decision drivers:** Display clarity for group viewing, reference tone capabilities, reliability, simplicity for student use
- **Tolerance for complexity:** Moderate; values features that support teaching but needs student-accessible interface

**Key Requirements:**
- Visual display legible from distance for group demonstrations
- Reference tone generation for group tuning exercises
- Reliable performance under continuous use during multi-hour rehearsals
- Simple enough for students to use independently with minimal instruction
- Professional accuracy to serve as authoritative teaching reference

**Representative Tasks:**
1. Project application display for ensemble to demonstrate target tuning
2. Generate reference tone for unison tuning exercise in group setting
3. Demonstrate concept of cents and pitch deviation to students
4. Verify student instrument tuning at lesson beginning
5. Recommend free application to students for home practice use

**Accommodation Strategy:**
- Design visual elements with sufficient size and contrast for distance viewing
- Ensure reference tone volume appropriate for classroom environment
- Maintain simple core functionality suitable for student self-service use
- Provide brief help documentation educators can reference when teaching concepts
- Ensure application stability under extended continuous use

#### 2.2.4 User Class Comparison

| Characteristic | Amateur Musicians | Professional Musicians | Music Educators |
|----------------|-------------------|------------------------|-----------------|
| **Priority Level** | Primary | Primary | Secondary |
| **Technical Expertise** | Low-Medium | Medium-High | Medium |
| **Music Theory Knowledge** | Low-Medium | High | High |
| **Accuracy Requirements** | ±2-3 cents acceptable | ±1 cent required | ±1 cent required |
| **Configuration Needs** | Minimal | Extensive | Moderate |
| **Usage Duration** | 2-5 minutes | 5-15 minutes | 30+ minutes |
| **Usage Environment** | Quiet home | Variable professional | Classroom/studio |
| **Primary Value** | Simplicity | Precision | Reliability + Teaching |

**Design Philosophy:**
Requirements prioritize delivering professional-grade accuracy and precision (satisfying Professional Musicians and Music Educators) while maintaining interface simplicity and clarity (satisfying Amateur Musicians). This approach ensures the application serves serious users without alienating casual users through unnecessary complexity.

### 2.3 Operating Environment

The application executes on consumer mobile devices in diverse environmental conditions. System requirements balance broad device compatibility with performance and accuracy standards.

#### 2.3.1 Hardware Environment

**iOS Device Requirements:**
- **Device types:** iPhone 6s or later models
- **Processor:** Apple A9 chip or later with 64-bit ARM architecture
- **Memory:** Minimum 2 GB RAM (3+ GB recommended for optimal performance)
- **Storage:** 25 MB free space for application installation
- **Display:** Touchscreen with minimum resolution 750x1334 pixels (iPhone 6s/7/8/SE2)
- **Audio input:** Built-in microphone or wired/Bluetooth headset microphone with frequency response covering 60 Hz - 4000 Hz minimum
- **Audio output:** Built-in speaker or wired/Bluetooth headset capable of 200 Hz - 600 Hz reproduction
- **Supported screen sizes:** 4.7" to 6.7" diagonal (responsive design adapts to all iPhone form factors)

**Android Device Requirements:**
- **Device types:** Smartphones meeting minimum specifications (tablets supported through responsive design but not optimized)
- **Processor:** ARM or x86 64-bit processor with minimum 1.4 GHz quad-core
- **Memory:** Minimum 2 GB RAM (3+ GB recommended for optimal performance)
- **Storage:** 25 MB free space for application installation
- **Display:** Touchscreen with minimum resolution 720x1280 pixels (HD)
- **Audio input:** Microphone with frequency response covering 60 Hz - 4000 Hz minimum; supports various hardware implementations across manufacturers
- **Audio output:** Speaker capable of 200 Hz - 600 Hz reproduction
- **Supported screen sizes:** 4.5" to 6.8" diagonal (responsive design adapts to common smartphone aspect ratios)

**Hardware Variability Considerations:**
- **Android fragmentation:** Broad manufacturer diversity (Samsung, Google, Xiaomi, OnePlus, Motorola, etc.) requires extensive device-specific testing due to varying microphone hardware quality, audio processing pipelines, and sample rate capabilities
- **Microphone quality:** Consumer device microphones vary significantly in noise floor, frequency response flatness, and phase characteristics; pitch detection algorithms must accommodate 40-70 dB SNR range
- **Speaker limitations:** Mobile device speakers emphasize mid-range frequencies; reference tone range limited to C4-C5 to ensure reliable reproduction across hardware variations
- **Touch screen precision:** Capacitive touchscreen accuracy sufficient for note selection and mode switching; no stylus or fine-motor precision required

#### 2.3.2 Software Environment

**iOS Platform Requirements:**
- **Operating system:** iOS 13.0 or later
- **Runtime environment:** Cocoa Touch framework, CoreAudio framework
- **Development tools:** Xcode 13.0 or later for compilation
- **Language runtime:** C++17 standard library (JUCE framework dependency)
- **Graphics API:** Metal for GPU-accelerated UI rendering where available
- **Audio API:** CoreAudio with Audio Unit framework for real-time audio processing

**Android Platform Requirements:**
- **Operating system:** Android 8.0 (API level 26) or later
- **Runtime environment:** Android Runtime (ART), Native Development Kit (NDK) for C++ code execution
- **Development tools:** Android Studio with NDK r21 or later
- **Language runtime:** C++17 standard library (JUCE framework dependency)
- **Graphics API:** OpenGL ES 2.0 or later for GPU-accelerated rendering
- **Audio API:** OpenSL ES or AAudio (API 27+) for low-latency audio processing

**Framework Dependencies:**
- **JUCE Framework:** Version 7.0 or later
  - Modules: juce_audio_basics, juce_audio_devices, juce_audio_processors, juce_dsp, juce_gui_basics, juce_gui_extra, juce_core, juce_data_structures, juce_events
  - License: JUCE Personal License (free for non-commercial distribution) or JUCE Pro License if commercial licensing needed
- **Standard C++ Library:** C++17 standard implementation (provided by platform toolchains)
- **No third-party dependencies:** Application uses only JUCE and platform-provided libraries to minimize version conflicts and simplify build process

**Platform Permissions:**
- **iOS:** `NSMicrophoneUsageDescription` key in Info.plist with explanation: "Microphone access required for pitch detection to analyze instrument sound and determine tuning accuracy."
- **Android:** `<uses-permission android:name="android.permission.RECORD_AUDIO"/>` in AndroidManifest.xml with runtime permission request dialog

**App Store Requirements:**
- **iOS:** Compliance with App Store Review Guidelines including privacy manifest, code signing with valid Developer Certificate
- **Android:** Compliance with Google Play policies including target SDK version within one year of latest release, 64-bit native library support

#### 2.3.3 Physical Environment

The application must function reliably in diverse acoustic environments where musicians practice and perform:

**Acoustic Conditions:**
- **Quiet environments:** Home practice rooms, private studios (30-40 dB ambient noise)
- **Moderate noise:** Ensemble rehearsal spaces, music classrooms (50-60 dB ambient noise)
- **Noisy environments:** Concert hall stages during setup, outdoor performance venues (60-70 dB ambient noise)

**Environmental Factors:**
- **Temperature range:** Device operation within manufacturer specifications (typically 0°C to 35°C for mobile devices)
- **Humidity:** Standard indoor conditions; no special water resistance requirements beyond device manufacturer specifications
- **Lighting:** User interface must remain legible under varied lighting from dimly-lit concert stages to bright outdoor daylight
- **Physical stability:** User may hold device or place on music stand during use; no specialized mounting hardware required

**Usage Scenarios:**
- **Stationary use:** Device placed on flat surface or music stand while playing instrument
- **Handheld use:** User holds device while tuning or selecting reference tones
- **Teaching/demonstration:** Device display visible to instructor and students in classroom setting
- **Performance preparation:** Quick tuning checks in stage wings or warm-up rooms
- **Travel:** Tuning in varied locations including airports, hotels, outdoor venues

**Connectivity Independence:**
The application must function reliably in:
- Locations without cellular data coverage (rural areas, basements, remote venues)
- Venues with congested WiFi networks (conference centers, performance halls)
- International locations where data roaming is disabled
- Airplane mode or cellular-disabled configurations
- Devices without cellular radios (WiFi-only tablets if supported in future)

### 2.4 Design and Implementation Constraints

The following constraints establish boundaries for architecture, technology selection, and implementation approaches.

#### 2.4.1 Framework and Technology Constraints

**CON-1: JUCE Framework Requirement**
- **Constraint:** Application must be implemented using JUCE framework version 7.0 or later
- **Rationale:** Cross-platform audio I/O abstraction and DSP utilities minimize platform-specific code; single codebase reduces maintenance burden
- **Impact:** Development team must have C++ and JUCE framework expertise; alternative frameworks (Flutter, React Native, native iOS/Android) are not options

**CON-2: Minimal Platform-Specific Code**
- **Constraint:** Platform-specific code (Objective-C++ for iOS, Java/Kotlin for Android) limited to essential functionality not abstracted by JUCE
- **Rationale:** Reduces code duplication, simplifies testing, maintains behavioral consistency across platforms
- **Impact:** Feature requests requiring extensive platform-specific implementation may be deferred or rejected

**CON-3: C++ Language Standard**
- **Constraint:** Implementation must use C++17 standard; C++20 or later features prohibited
- **Rationale:** Ensures compatibility with JUCE framework and Android NDK compiler toolchains
- **Impact:** Modern C++ features from C++20+ (concepts, ranges, coroutines) unavailable

**CON-4: No Third-Party Audio Libraries**
- **Constraint:** Audio processing, autocorrelation algorithms, and DSP operations must use JUCE-provided or self-implemented code; no external audio libraries
- **Rationale:** Minimizes dependency conflicts, licensing complications, and binary size growth
- **Impact:** Advanced DSP techniques not provided by JUCE require custom implementation

#### 2.4.2 Performance and Resource Constraints

**CON-5: Real-Time Audio Processing**
- **Constraint:** Pitch detection and tone generation must execute within audio callback deadlines without blocking or glitching
- **Rationale:** Audio thread cannot tolerate latency; missed deadlines cause audible artifacts unacceptable in tuning application
- **Impact:** Memory allocations, file I/O, network operations, and complex computations prohibited in audio callback; requires careful algorithm selection and optimization

**CON-6: Low-Latency Requirement**
- **Constraint:** Pitch detection latency from microphone input to display update must not exceed 100ms on 90% of supported devices
- **Rationale:** Sub-100ms latency provides responsive feedback. 4096-sample buffer (93ms @ 44.1kHz) required for accurate C1 detection (lowest note in range)
- **Impact:** Requires efficient autocorrelation computation, optimized pitch period analysis algorithms, and minimal UI update overhead

**CON-7: Application Size Limit**
- **Constraint:** Final application binary must not exceed 25 MB installed size
- **Rationale:** Minimizes download barriers on cellular connections and device storage concerns
- **Impact:** Restricts inclusion of large assets, requires code optimization, prevents embedding extensive help documentation or media files

**CON-8: Memory Footprint**
- **Constraint:** Application memory usage must not exceed 50 MB during normal operation
- **Rationale:** Prevents memory warnings and forced termination on devices with 2 GB RAM
- **Impact:** Limits audio buffer sizes, autocorrelation buffer lengths, and UI complexity; requires efficient memory management

**CON-9: CPU Utilization**
- **Constraint:** Audio processing must not exceed 15% CPU utilization on target devices; UI rendering must not drop below 30 FPS
- **Rationale:** Prevents device heating, battery drain, and interference with system responsiveness
- **Impact:** Requires optimized algorithms, potentially limiting real-time analysis complexity or visual effects

#### 2.4.3 Platform and Regulatory Constraints

**CON-10: Mobile Platform Guidelines**
- **Constraint:** Application must comply with iOS Human Interface Guidelines and Android Material Design principles
- **Rationale:** Platform consistency improves usability and is required for app store approval
- **Impact:** UI design must follow platform conventions for navigation, touch targets, visual hierarchy; complete design freedom not available

**CON-11: App Store Requirements**
- **Constraint:** Application must pass Apple App Store Review Guidelines and Google Play Developer Policy review
- **Rationale:** Distribution through official stores is primary deployment method
- **Impact:** Cannot implement features that violate store policies (e.g., private API usage on iOS, background recording without notification on Android)

**CON-12: Privacy Regulations**
- **Constraint:** Application must comply with GDPR, CCPA, and platform privacy policies regarding data collection and usage
- **Rationale:** Legal compliance required for distribution in EU, California, and app stores
- **Impact:** No user data collection, analytics, or tracking beyond platform-provided opt-in mechanisms; requires privacy policy documentation

**CON-13: Accessibility Baseline**
- **Constraint:** Application must support platform-standard screen readers (VoiceOver on iOS, TalkBack on Android) at basic level
- **Rationale:** App store guidelines encourage accessibility; ethical imperative for inclusive design
- **Impact:** UI elements must have accessible labels; complex visual tuning meter may have limited accessibility (noted as future enhancement area)

**CON-14: Background Execution Limitations**
- **Constraint:** Application cannot process audio when in background state due to platform restrictions and battery conservation policies
- **Rationale:** Mobile platforms aggressively suspend background processes to preserve battery life
- **Impact:** Pitch detection and tone generation cease when user switches to another application; no background tuning mode possible

#### 2.4.4 Operational Constraints

**CON-15: Offline-Only Operation**
- **Constraint:** Application must not transmit or receive network data for any functionality; all processing occurs on-device
- **Rationale:** Core business requirement ensuring functionality without connectivity; privacy benefit avoiding data transmission
- **Impact:** No remote configuration, cloud settings synchronization, usage analytics telemetry, crash reporting beyond platform-provided opt-in systems, or update notifications beyond app store mechanisms

**CON-16: No External Data Dependencies**
- **Constraint:** Application cannot require downloads of additional data files, models, or resources after installation
- **Rationale:** Supports offline-only requirement and ensures predictable first-launch experience
- **Impact:** All algorithms, UI resources, and help content must be bundled in initial application binary

**CON-17: Minimal User Configuration**
- **Constraint:** Application must function with acceptable results using default settings; advanced configuration optional
- **Rationale:** Reduces barrier to entry for amateur musicians unfamiliar with tuning concepts
- **Impact:** Algorithms must adapt to hardware variability without manual calibration; sensible defaults for reference pitch and detection sensitivity

**CON-18: No User Account System**
- **Constraint:** Application operates without user registration, authentication, or account management
- **Rationale:** Simplifies privacy model, removes network dependency, reduces implementation complexity
- **Impact:** No user-specific preferences synchronization across devices; each device installation independent

#### 2.4.5 Development and Maintenance Constraints

**CON-19: Volunteer Development Resources**
- **Constraint:** Development relies on volunteer contributors without guaranteed availability or paid development time
- **Rationale:** Free application model generates no revenue for paid development
- **Impact:** Feature complexity must accommodate intermittent development cycles; extensive testing on numerous devices may be limited

**CON-20: Limited Device Testing Infrastructure**
- **Constraint:** Physical device testing limited to approximately 3 iOS devices and 5 Android devices owned by development team
- **Rationale:** Budget constraints prevent purchasing comprehensive device testing lab
- **Impact:** Cannot exhaustively test all device models; must rely on conservative algorithm design and beta tester feedback

**CON-21: Open-Source Licensing Considerations**
- **Constraint:** If project adopts open-source license, must ensure JUCE license compatibility and clearly document licensing terms
- **Rationale:** JUCE Personal License permits non-commercial open-source use; commercial licensing may be required if business model changes
- **Impact:** License selection impacts future monetization options and contribution model

**CON-21: Desktop Testing Infrastructure**
**Priority:** HIGH
**Constraint:** Development workflow shall include desktop-based testing capability to enable rapid iteration and automated testing without requiring mobile device deployment.

**Impact:**
- Requires dual build system support (CMake for desktop, Projucer for mobile)
- Requires platform abstraction layer for testability
- Influences architecture to separate platform-dependent code
- Enables CI/CD automation without mobile device infrastructure

**Justification:**
- Mobile device testing is slow and resource-intensive
- Automated testing requires desktop test harness
- Reduces development cycle time significantly
- Enables unit testing in CI/CD pipeline

**CON-22: Continuous Integration Limitations**
- **Constraint:** Build automation may be limited to basic compilation testing without extensive device emulation or performance testing
- **Rationale:** Advanced CI/CD infrastructure requires paid services or significant configuration effort
- **Impact:** Manual testing remains primary quality assurance method; automated performance regression detection limited

### 2.5 Assumptions and Dependencies

This section documents assumptions about the operating environment, user capabilities, and external factors that, if invalidated, may impact system requirements or project success.

#### 2.5.1 Hardware Assumptions

**AS-HW-1: Microphone Frequency Response**
- **Assumption:** Target devices have microphones capable of capturing audio in the 32-4186 Hz range with signal-to-noise ratio of at least 40 dB
- **Validation:** Consumer device microphones typically optimize 100-3500 Hz range; may have reduced sensitivity at frequency extremes
- **Risk if invalid:** Low-frequency instruments (bass guitar C1 at 32.7 Hz) or high-pitched instruments (piccolo C8 at 4186 Hz) may not detect reliably
- **Mitigation:** Focus testing on mid-range instruments (guitar, violin, voice); document frequency range limitations if edge cases fail

**AS-HW-2: Speaker Capability**
- **Assumption:** Device speakers can reproduce reference tones in 261-523 Hz range (C4-C5) with sufficient volume and minimal distortion
- **Validation:** Mobile speakers optimize mid-range frequencies; bass response typically weak below 200 Hz
- **Risk if invalid:** Reference tones may sound quiet, distorted, or inaudible on devices with poor speaker quality
- **Mitigation:** Limit reference tone range to octave where speakers perform adequately; test volume levels across device models

**AS-HW-3: Touch Screen Precision**
- **Assumption:** Capacitive touchscreens provide sufficient accuracy for note selection and mode switching without requiring stylus
- **Validation:** Standard touch target size guidelines (minimum 44x44 points iOS, 48x48 dp Android) ensure reliable interaction
- **Risk if invalid:** Users may struggle to select correct notes or accidentally trigger wrong controls
- **Mitigation:** Design UI elements meeting platform touch target size guidelines; provide adequate spacing between interactive elements

**AS-HW-4: Display Resolution**
- **Assumption:** Minimum display resolution (750x1334 iOS, 720x1280 Android) provides sufficient pixel density for clear text and tuning meter rendering
- **Validation:** Modern smartphones exceed minimum resolution; responsive design scales to available screen space
- **Risk if invalid:** Text may be illegible or tuning meter insufficiently precise on low-resolution devices
- **Mitigation:** Test on minimum-specification devices; adjust font sizes and meter precision to maintain usability

**AS-HW-5: Processing Power**
- **Assumption:** Target device CPUs can execute autocorrelation-based pitch detection algorithms within real-time constraints on audio thread
- **Validation:** Modern mobile processors include SIMD instructions (NEON on ARM) and multi-core architectures enabling efficient DSP
- **Risk if invalid:** Older or low-end devices may experience audio dropouts, high latency, or excessive battery drain
- **Mitigation:** Optimize algorithms for efficiency; test performance on minimum-specification devices; document device compatibility limitations if necessary

#### 2.5.2 Software and Platform Assumptions

**AS-SW-1: Platform API Stability**
- **Assumption:** iOS and Android audio APIs remain stable or provide backward compatibility during application lifecycle
- **Validation:** Platform vendors maintain multi-year API compatibility policies
- **Risk if invalid:** OS updates may break audio functionality, requiring emergency patches or compatibility workarounds
- **Mitigation:** Follow platform best practices; use documented APIs rather than private interfaces; test on beta OS versions when available

**AS-SW-2: JUCE Framework Support**
- **Assumption:** JUCE framework continues supporting iOS and Android platforms with maintained audio and GUI modules
- **Validation:** JUCE has 20+ year history of active development and platform support
- **Risk if invalid:** Framework abandonment or license changes could require migration to alternative framework
- **Mitigation:** Monitor JUCE development activity; maintain modular architecture enabling framework substitution; ensure license permits long-term use

**AS-SW-3: Permission Model Compliance**
- **Assumption:** Users grant microphone permission when requested; denial does not prevent application launch
- **Validation:** Platform guidelines require graceful handling of permission denial
- **Risk if invalid:** Core functionality (pitch detection) unavailable without microphone access
- **Mitigation:** Detect permission status; display clear explanation of microphone necessity; provide direct link to system settings for permission modification

**AS-SW-4: App Store Distribution**
- **Assumption:** Apple App Store and Google Play Store remain available for free application distribution without prohibitive fees
- **Validation:** Current platform policies permit free applications; developer account fees ($99/year iOS, $25 one-time Android) are acceptable
- **Risk if invalid:** Alternative distribution methods (side-loading, third-party stores) have limited reach and user trust
- **Mitigation:** Maintain compliance with store policies; consider secondary distribution channels if policies change adversely

**AS-SW-5: No Background Processing**
- **Assumption:** Users accept that tuning functionality ceases when application is backgrounded; no expectation of continuous monitoring
- **Validation:** Musicians typically focus on single task during tuning; application switching during tuning unusual
- **Risk if invalid:** Users may expect background operation similar to music player applications
- **Mitigation:** Clearly document foreground-only operation in app description and help content; resume immediately when returning to foreground

#### 2.5.3 User Assumptions

**AS-USER-1: Basic Music Terminology**
- **Assumption:** Users understand basic musical concepts including note names (A, B, C, etc.), octave numbers, and flat/sharp terminology
- **Validation:** These concepts are taught in introductory music education
- **Risk if invalid:** Users may not understand which note they are tuning or how to interpret display
- **Mitigation:** Provide brief in-app help with note name chart and explanation of tuning indicators; visual indicators (flat/center/sharp) reduce need for terminology knowledge

**AS-USER-2: Tuning Concept Familiarity**
- **Assumption:** Users understand goal is to bring instrument pitch into alignment with target frequency
- **Validation:** Musicians of all levels encounter tuning as fundamental activity
- **Risk if invalid:** Users may not understand application purpose or how to use feedback to adjust instrument
- **Mitigation:** Provide visual indicators clearly showing direction of adjustment needed (tune up or down)

**AS-USER-3: Microphone Permission Understanding**
- **Assumption:** Users understand microphone access is required for pitch detection and will grant permission
- **Validation:** Users commonly grant permissions to legitimate applications with clear usage explanations
- **Risk if invalid:** Permission denial prevents core functionality; users may rate application negatively
- **Mitigation:** Provide clear, specific explanation in permission request dialog; offer help content explaining necessity

**AS-USER-4: Smartphone Operation Skills**
- **Assumption:** Users possess basic smartphone operation skills including app installation, launching, touch interaction, and navigation
- **Validation:** Smartphone adoption widespread; musicians likely own devices given prevalence
- **Risk if invalid:** Very inexperienced users may struggle with application installation or basic operation
- **Mitigation:** Maintain simple, intuitive interface following platform conventions; minimize navigation complexity

**AS-USER-5: Acoustic Isolation Awareness**
- **Assumption:** Users understand microphone captures all audible sound; background noise degrades pitch detection accuracy
- **Validation:** Musicians generally tune in relatively quiet environments
- **Risk if invalid:** Users in noisy environments may experience poor detection accuracy and perceive application as faulty
- **Mitigation:** Include help content advising quiet environment usage; algorithms should reject highly ambiguous detections rather than displaying erratic results

#### 2.5.4 Environmental Assumptions

**AS-ENV-1: Adequate Acoustic Conditions**
- **Assumption:** Users operate application in environments with ambient noise levels permitting clear instrument sound capture (signal 20+ dB above noise floor)
- **Validation:** Typical practice and performance venues provide adequate signal-to-noise ratio
- **Risk if invalid:** High ambient noise (loud rehearsals, outdoor wind noise) may prevent accurate detection
- **Mitigation:** Algorithms should detect low-confidence readings and indicate uncertainty rather than displaying incorrect results

**AS-ENV-2: Standard Room Acoustics**
- **Assumption:** Room acoustics do not create excessive reverberation or resonance significantly distorting captured audio
- **Validation:** Most practice environments have acceptable acoustic properties for pitch detection
- **Risk if invalid:** Highly reverberant spaces may cause detection errors from overlapping reflections
- **Mitigation:** McLeod PPM autocorrelation approach naturally handles moderate reverberation; test in various acoustic spaces

**AS-ENV-3: Device Positioning**
- **Assumption:** Users position device microphone within 0.3-2 meters of instrument sound source for adequate signal level
- **Validation:** Natural usage patterns place device on music stand or nearby surface
- **Risk if invalid:** Excessive distance or microphone obstruction may reduce signal level below detection threshold
- **Mitigation:** Provide help content suggesting optimal device positioning; design algorithms with wide dynamic range

#### 2.5.5 External Dependencies

**DE-EXT-1: JUCE Framework Availability**
- **Dependency:** JUCE framework version 7.0+ remains available with compatible licensing for free application distribution
- **Criticality:** HIGH - Core framework enabling cross-platform development
- **Contingency:** If JUCE license changes prohibit free distribution, options include: (1) negotiate alternative licensing, (2) migrate to alternative framework (significant rework), (3) restrict distribution or implement paid model

**DE-EXT-2: Platform SDK Access**
- **Dependency:** Apple and Google provide free access to iOS SDK (via Xcode) and Android SDK (via Android Studio) for development
- **Criticality:** HIGH - Essential for compilation and testing
- **Contingency:** Platform vendors consistently provide free development tools; risk extremely low

**DE-EXT-3: App Store Distribution Channels**
- **Dependency:** Apple App Store and Google Play Store accept free application submissions and maintain distribution infrastructure
- **Criticality:** HIGH - Primary distribution method reaching target users
- **Contingency:** If store policies change adversely, alternative distribution includes: (1) direct download from website (iOS requires enterprise certificate or TestFlight, Android permits APK side-loading), (2) alternative app stores (Amazon Appstore, F-Droid for open source)

**DE-EXT-4: Development Tool Chains**
- **Dependency:** Xcode (macOS) for iOS builds, Android Studio for Android builds remain available without prohibitive licensing costs
- **Criticality:** HIGH - Required for compilation and deployment
- **Contingency:** Current free availability expected to continue; both vendors maintain these tools for ecosystem health

**DE-EXT-5: Testing Device Access**
- **Dependency:** Development team maintains access to representative iOS and Android devices for testing
- **Criticality:** MEDIUM - Essential for quality assurance but could rely more heavily on beta testers
- **Contingency:** If physical device access limited, increase reliance on: (1) beta testing program with diverse user device pool, (2) device simulators/emulators for basic functionality testing (noting simulators cannot test real audio I/O)

**DE-EXT-6: Standard C++ Library**
- **Dependency:** Platform compilers provide conformant C++17 standard library implementations
- **Criticality:** HIGH - Required for code compilation
- **Contingency:** Modern platforms consistently provide standard-conformant toolchains; risk extremely low

**DE-EXT-7: No External Services**
- **Dependency:** Explicitly NO dependencies on cloud services, remote APIs, content delivery networks, or third-party services
- **Criticality:** N/A - Offline-only design deliberately avoids external service dependencies
- **Advantage:** Eliminates risks associated with service availability, API changes, authentication failures, or cost increases from third-party providers

#### 2.5.6 Assumption Validation and Risk Management

The development team should validate critical assumptions through:

1. **Hardware testing:** Verify microphone and speaker capabilities on minimum-specification devices from assumption AS-HW-1 and AS-HW-2
2. **Platform research:** Monitor iOS and Android development announcements for API changes affecting assumptions AS-SW-1 and AS-SW-2
3. **Beta testing:** Recruit diverse user population to validate user assumptions AS-USER-1 through AS-USER-5
4. **Acoustic testing:** Evaluate pitch detection accuracy in varied environmental conditions validating AS-ENV-1 through AS-ENV-3

Regular assumption review should occur at project milestones to identify invalidated assumptions requiring requirement adjustments or risk mitigation activations.

---

## 3. System Features

This section details the functional requirements for each major system feature. Requirements are organized by feature and assigned unique identifiers for traceability. All requirements classified as CRITICAL are mandatory for Version 1.0 release.

### 3.1 System Feature: Pitch Detection and Display (Meter Mode)

#### 3.1.1 Description

Meter Mode provides real-time chromatic pitch detection by continuously analyzing microphone input and displaying the detected note name, octave, pitch deviation in cents, and visual tuning indicators. This mode operates automatically without requiring manual note selection, accommodating musicians tuning any chromatic instrument across a seven-octave range.

The system employs the McLeod Pitch Period Method using autocorrelation-based analysis to identify the fundamental frequency of incoming audio, maps detected frequencies to the nearest note in 12-tone equal temperament, calculates deviation from the target frequency in cents, and updates the visual display with minimal latency. The analog-style tuning meter provides intuitive visual feedback through needle position, colored zones, and reference markings.

**Priority:** CRITICAL  
**Stimulus/Response Sequences:**
1. User launches application in Meter Mode (default)
2. System requests microphone permission if not previously granted
3. User grants permission and plays instrument note
4. System detects fundamental frequency, identifies note, calculates cent deviation
5. System updates display showing note name, octave, meter needle position, and tuning status

**Functional Requirements:**

**FR-001: Continuous Audio Monitoring**  
**Priority:** CRITICAL  
The system shall continuously monitor microphone input when Meter Mode is active and the application is in the foreground, processing audio buffers at the device's native sample rate (typically 44.1 kHz or 48 kHz).

**FR-002: Frequency Range Coverage**  
**Priority:** CRITICAL  
The system shall detect fundamental frequencies across the range from 32.70 Hz (C1) to 4186.01 Hz (C8), encompassing seven complete octaves of chromatic pitch detection.

**FR-003: Fundamental Frequency Extraction**
**Priority:** CRITICAL
The system shall extract the fundamental frequency from audio input using the McLeod Pitch Period Method with autocorrelation-based analysis, achieving a minimum frequency resolution of 0.5 Hz and distinguishing between fundamental and harmonic overtones using the Normalized Square Difference Function (NSDF).

**FR-004: Noise Rejection**  
**Priority:** HIGH  
The system shall reject audio input below a minimum signal threshold of -40 dBFS to prevent noise from triggering false detections in the absence of musical input.

**FR-005: Chromatic Note Identification**  
**Priority:** CRITICAL  
The system shall map detected fundamental frequencies to the nearest note in the 12-tone equal temperament scale using the formula:

```
note_number = round(12 × log₂(f / f_ref))
where f_ref is the frequency of the reference pitch (default A4 = 440 Hz)
```

The system shall identify note names as: C, C#, D, D#, E, F, F#, G, G#, A, A#, B.

**FR-006: Octave Number Assignment**  
**Priority:** CRITICAL  
The system shall assign octave numbers from 1 to 8 using scientific pitch notation where:
- C4 = 261.63 Hz (middle C)
- A4 = reference pitch frequency (default 440 Hz)
- Each octave begins at C and ends at B

**FR-007: Cent Deviation Calculation**  
**Priority:** CRITICAL  
The system shall calculate pitch deviation in cents from the target note frequency using the formula:

```
cents = 1200 × log₂(f_detected / f_target)
```

The system shall display cent values with precision of ±0.1 cents and shall display the calculated deviation in the range -50.0 to +50.0 cents.

**FR-008: Detection Accuracy**  
**Priority:** CRITICAL  
The system shall achieve pitch detection accuracy within ±1 cent of the actual fundamental frequency for input signals with signal-to-noise ratio of 40 dB or greater and stable pitch lasting at least 100 ms.

**FR-009: Note Name Display**  
**Priority:** CRITICAL  
The system shall display the detected note name (e.g., "A", "C#", "Eb") and octave number (e.g., "4", "3", "5") with font size occupying at least 15% of screen height in portrait orientation, ensuring legibility from typical viewing distances of 30-100 cm.

**FR-010: Tuning Meter Visualization**  
**Priority:** CRITICAL  
The system shall display an analog-style tuning meter consisting of:
- Horizontal arc spanning at least 120 degrees of visual angle
- Cent scale markings at minimum intervals of 10 cents from -50 to +50
- Animated needle indicating current pitch deviation position
- Needle movement smoothed with damping coefficient to prevent excessive oscillation while maintaining responsiveness to genuine pitch changes

**FR-011: Flat Indicator**  
**Priority:** CRITICAL  
The system shall display a visual "FLAT" indicator (colored zone, text label, or icon) when the detected pitch is more than 5 cents below the target frequency (-50.0 to -5.1 cents).

**FR-012: Center (In Tune) Indicator**  
**Priority:** CRITICAL  
The system shall display a visual "IN TUNE" or center zone indicator when the detected pitch is within ±5.0 cents of the target frequency, using distinct color (typically green) and optional haptic feedback if supported.

**FR-013: Sharp Indicator**  
**Priority:** CRITICAL  
The system shall display a visual "SHARP" indicator (colored zone, text label, or icon) when the detected pitch is more than 5 cents above the target frequency (+5.1 to +50.0 cents).

**FR-014: Pure Major Third Reference Mark**  
**Priority:** MEDIUM  
The system shall display a reference mark on the tuning meter at -13.7 cents indicating the position of a pure major third interval (frequency ratio 5:4) relative to equal temperament, assisting musicians working with just intonation or historical temperaments.

**FR-015: Pure Minor Third Reference Mark**  
**Priority:** MEDIUM  
The system shall display a reference mark on the tuning meter at +15.6 cents indicating the position of a pure minor third interval (frequency ratio 6:5) relative to equal temperament.

**FR-016: Cent Value Numeric Display**  
**Priority:** HIGH  
The system shall display the numeric cent deviation value with sign (e.g., "-12.3", "+3.7", "0.0") using font size at least 8% of screen height, positioned adjacent to the tuning meter for users preferring numerical feedback.

**FR-017: Detection Confidence Handling**  
**Priority:** HIGH  
The system shall display a "no signal" or inactive state when:
- No audio input exceeds the minimum threshold for 500 ms
- Detected signal is highly ambiguous (multiple competing fundamental frequency candidates with similar confidence)
- Input contains excessive broadband noise preventing reliable fundamental frequency extraction

**FR-018: Pitch Detection Latency**  
**Priority:** CRITICAL  
The system shall update the display with newly detected pitch information within 100 ms of the corresponding audio arriving at the microphone input on devices meeting minimum hardware specifications.

**FR-019: Display Update Rate**  
**Priority:** HIGH  
The system shall refresh the tuning meter needle position and cent value at a minimum rate of 20 Hz (50 ms intervals) to provide smooth visual feedback during pitch adjustments.

**FR-020: Stable Note Persistence**  
**Priority:** MEDIUM  
When the detected note name changes, the system shall display the new note only after it remains the most likely candidate for at least 100 ms to prevent rapid flickering between adjacent notes during pitch transitions.

**FR-021: Reference Pitch Integration**  
**Priority:** CRITICAL  
The system shall recalculate all target note frequencies based on the current reference pitch (A4) setting when the user modifies the reference pitch calibration, immediately affecting pitch detection and cent deviation calculations without requiring application restart.

**FR-022: Meter Mode Activation**  
**Priority:** CRITICAL  
The system shall activate Meter Mode when:
- The application launches (default mode)
- The user explicitly switches from Sound Mode to Meter Mode via mode selection control
- Sound Mode tone generation is deactivated

**FR-023: Meter Mode Deactivation**  
**Priority:** CRITICAL  
The system shall deactivate pitch detection and cease updating the display when:
- The user switches to Sound Mode with active tone generation
- The application enters background state
- Microphone permission is revoked

---

### 3.2 System Feature: Reference Tone Generation (Sound Mode)

#### 3.2.1 Description

Sound Mode enables users to generate continuous reference tones for aural tuning by selecting a note from a one-octave chromatic range and toggling tone playback on or off. The system synthesizes pure sine wave tones at precise frequencies corresponding to 12-tone equal temperament, providing an auditory reference for pitch matching.

This feature supports musicians who prefer tuning by ear, music educators demonstrating target pitches, and scenarios where visual tuning is impractical. The toggle control provides immediate tone activation and deactivation without latency, allowing efficient workflows for quick reference checks.

**Priority:** CRITICAL  
**Stimulus/Response Sequences:**
1. User switches to Sound Mode via mode selection control
2. System displays note selection interface showing C4 through C5
3. User selects desired reference note (e.g., A4)
4. User presses toggle control to activate tone
5. System generates continuous sine wave at precise frequency
6. User presses toggle control again to deactivate tone

**Functional Requirements:**

**FR-024: Note Selection Range**  
**Priority:** CRITICAL  
The system shall provide note selection for one chromatic octave from C4 (261.63 Hz) to C5 (523.25 Hz), inclusive of all twelve notes: C4, C#4, D4, D#4, E4, F4, F#4, G4, G#4, A4, A#4, B4, C5.

**FR-025: Note Selection Interface**  
**Priority:** CRITICAL  
The system shall display a note selection interface using one of the following approaches:
- Touch-responsive visual keyboard showing all 13 notes (12 chromatic notes plus C5 octave)
- Scrollable or swipeable note picker
- Grid of labeled buttons for each note

Each selectable note element shall meet minimum touch target size of 44×44 points (iOS) or 48×48 dp (Android).

**FR-026: Selected Note Indication**  
**Priority:** HIGH  
The system shall visually indicate the currently selected note through highlighting, border emphasis, or color change, ensuring users can identify which note will play when tone generation is activated.

**FR-027: Tone Toggle Control**  
**Priority:** CRITICAL  
The system shall provide a toggle control (button or switch) that:
- Activates continuous tone generation when pressed in the inactive state
- Deactivates continuous tone generation when pressed in the active state
- Clearly indicates current state through visual design (e.g., "Play" vs "Stop", toggle position, color change)

**FR-028: Tone Generation Activation**  
**Priority:** CRITICAL  
When the user activates the toggle control, the system shall begin generating a continuous sine wave tone at the frequency corresponding to the selected note within 10 ms, ensuring zero perceptible latency.

**FR-029: Tone Generation Deactivation**  
**Priority:** CRITICAL  
When the user deactivates the toggle control, the system shall cease tone generation within 10 ms, applying a fade-out envelope of 5-10 ms duration to prevent audible clicking artifacts.

**FR-030: Frequency Calculation**  
**Priority:** CRITICAL  
The system shall calculate reference tone frequencies using 12-tone equal temperament based on the current reference pitch (A4) setting:

```
f(n) = f_A4 × 2^((n - 9) / 12)
where:
  n = number of semitones from C4 (C4=0, C#4=1, ..., A4=9, ..., C5=12)
  f_A4 = reference pitch frequency (default 440 Hz, user-configurable)
```

**FR-031: Tone Generation Accuracy**  
**Priority:** CRITICAL  
The system shall generate reference tones with frequency accuracy within ±1.5 cents of the calculated target frequency for the selected note.

**FR-032: Waveform Synthesis**  
**Priority:** CRITICAL  
The system shall synthesize reference tones as pure sine waves (single fundamental frequency with no harmonic content) to provide unambiguous pitch reference free from timbral complexity.

**FR-033: Amplitude Stability**  
**Priority:** HIGH  
The system shall maintain constant amplitude during tone generation with variation less than ±0.5 dB to ensure consistent reference volume.

**FR-034: Output Volume Level**  
**Priority:** HIGH  
The system shall generate reference tones at amplitude level producing comfortable listening volume through device speakers (approximately -12 dBFS to -6 dBFS), adjustable by device system volume controls but not requiring excessive volume to be audible.

**FR-035: Tone Continuity**  
**Priority:** CRITICAL  
The system shall maintain continuous tone generation without interruption, clicks, pops, or dropouts for the entire duration the toggle control remains in the active state.

**FR-036: Note Change During Playback**  
**Priority:** HIGH  
The system shall support changing the selected note while tone generation is active, immediately transitioning to the new frequency with crossfade duration of 50-100 ms to prevent audible clicking.

**FR-037: Reference Pitch Integration**  
**Priority:** CRITICAL  
The system shall recalculate and apply new tone frequencies immediately when the user modifies the reference pitch (A4) calibration setting:
- If tone is currently playing, frequency shall transition smoothly to new value within 100 ms
- If tone is inactive, the new frequency shall apply when next activated

**FR-038: Simultaneous Mode Exclusion**  
**Priority:** CRITICAL  
The system shall prevent simultaneous operation of Meter Mode and Sound Mode:
- When Sound Mode tone is activated, pitch detection shall be suspended
- When user switches to Meter Mode while tone is playing, tone generation shall deactivate automatically

**FR-039: Speaker Output Routing**  
**Priority:** CRITICAL  
The system shall route generated tones to the device's primary speaker output or user-connected audio output (wired headphones, Bluetooth headphones) according to iOS/Android audio routing policies.

**FR-040: Background Deactivation**  
**Priority:** CRITICAL  
The system shall automatically deactivate tone generation when the application enters background state to comply with platform policies and conserve resources, resuming only when user returns to foreground and explicitly reactivates the toggle control.

**FR-041: Tone Generation CPU Efficiency**  
**Priority:** HIGH  
The system shall generate reference tones using efficient sine wave synthesis algorithms consuming less than 3% CPU on minimum-specification devices to prevent device heating and battery drain during extended use.

**FR-042: Audio Session Configuration**  
**Priority:** HIGH  
The system shall configure the platform audio session for playback with appropriate audio category (iOS: AVAudioSessionCategoryPlayback, Android: USAGE_MEDIA) to ensure tones play through device speakers even when device is in silent mode where appropriate.

---

### 3.3 System Feature: Reference Pitch Calibration

#### 3.3.1 Description

Reference pitch calibration enables users to adjust the A4 frequency that serves as the tuning standard for all pitch detection and tone generation. This feature accommodates regional variations, historical performance practices, ensemble standards, and personal preferences by allowing fine-grained adjustment of the reference pitch from 410 Hz to 480 Hz in 1 Hz increments.

The default setting of 440 Hz represents international concert pitch, while common alternatives include 442 Hz (common in orchestras), 415 Hz (Baroque pitch), and 432 Hz (alternative tuning preference). The selected reference pitch persists across application sessions and immediately affects all frequency calculations.

**Priority:** CRITICAL  
**Stimulus/Response Sequences:**
1. User navigates to settings or calibration interface
2. System displays current reference pitch value (e.g., 440 Hz)
3. User adjusts reference pitch using increment/decrement controls or direct input
4. System updates reference pitch and immediately recalculates all note frequencies
5. User returns to Meter or Sound Mode
6. System applies new reference pitch to all operations

**Functional Requirements:**

**FR-043: Reference Pitch Range**  
**Priority:** CRITICAL  
The system shall allow users to set the A4 reference pitch to any integer frequency value from 410 Hz to 480 Hz inclusive, covering common historical and contemporary tuning standards.

**FR-044: Reference Pitch Increment**  
**Priority:** CRITICAL  
The system shall provide reference pitch adjustment in 1 Hz increments, enabling fine-grained calibration to match specific ensemble or performance requirements.

**FR-045: Default Reference Pitch**  
**Priority:** CRITICAL  
The system shall initialize the reference pitch to 440 Hz on first application launch, representing ISO 16:1975 international standard concert pitch.

**FR-046: Reference Pitch Display**  
**Priority:** CRITICAL  
The system shall display the current reference pitch value numerically with units (e.g., "440 Hz", "442 Hz") using font size at least 6% of screen height, ensuring clear visibility during adjustment.

**FR-047: Increment Control**  
**Priority:** CRITICAL  
The system shall provide a control (button, stepper, or swipe gesture) to increment the reference pitch by 1 Hz, wrapping from 480 Hz to 480 Hz (no wrap) when attempting to increment beyond the maximum.

**FR-048: Decrement Control**  
**Priority:** CRITICAL  
The system shall provide a control (button, stepper, or swipe gesture) to decrement the reference pitch by 1 Hz, stopping at 410 Hz when attempting to decrement below the minimum.

**FR-049: Direct Input Option**  
**Priority:** MEDIUM  
The system should provide an optional numeric input field allowing users to directly enter the desired reference pitch value, validating that input falls within the 410-480 Hz range and rounding to nearest integer.

**FR-050: Reset to Default**  
**Priority:** MEDIUM  
The system should provide a control to reset the reference pitch to 440 Hz (default value) with a single action, facilitating quick return to standard concert pitch.

**FR-051: Common Presets**  
**Priority:** LOW  
The system may provide quick-select presets for common reference pitches:
- 440 Hz (International standard)
- 442 Hz (Orchestra standard)
- 432 Hz (Alternative tuning)
- 415 Hz (Baroque pitch)

**FR-052: Immediate Application**  
**Priority:** CRITICAL  
The system shall immediately apply reference pitch changes to all frequency calculations:
- Meter Mode: Update target frequencies for all notes, affecting cent deviation calculations for currently detected pitch
- Sound Mode: Update generated tone frequency if tone is currently playing
- No application restart or mode switching required

**FR-053: Frequency Recalculation**  
**Priority:** CRITICAL  
When reference pitch changes, the system shall recalculate all note frequencies in the chromatic scale using the formula:

```
f(note) = f_A4 × 2^((n - 57) / 12)
where:
  f_A4 = current reference pitch setting
  n = MIDI note number (C4 = 60, A4 = 69)
```

**FR-054: Persistent Storage**  
**Priority:** CRITICAL  
The system shall persistently store the user's reference pitch setting using platform-provided local storage mechanisms (iOS: UserDefaults, Android: SharedPreferences), ensuring the setting persists across application launches and device restarts.

**FR-055: Storage Reliability**  
**Priority:** HIGH  
The system shall validate the stored reference pitch value on application launch and revert to 440 Hz default if:
- No stored value exists (first launch)
- Stored value is corrupted or outside valid range
- Storage access fails

**FR-056: Settings Access**  
**Priority:** HIGH  
The system shall provide access to reference pitch calibration through a dedicated settings screen or calibration control accessible from the main interface within 2 taps/interactions maximum.

**FR-057: Visual Feedback During Adjustment**  
**Priority:** MEDIUM  
The system should provide real-time visual feedback during reference pitch adjustment:
- Meter Mode: Show how cent deviation reading changes for currently detected note
- Sound Mode: Immediately play updated frequency if tone is active

**FR-058: Calibration Range Indicators**  
**Priority:** LOW  
The system may display visual indicators showing position within the 410-480 Hz range (e.g., slider, progress indicator) to help users understand proximity to range limits.

**FR-059: A4 Frequency Display Precision**  
**Priority:** HIGH  
The system shall display reference pitch values as integers without decimal places (e.g., "440 Hz", not "440.0 Hz") since adjustment occurs in 1 Hz increments.

---

### 3.4 System Feature: User Interface and Orientation Handling

#### 3.4.1 Description

The user interface provides intuitive access to all application features through a touch-optimized design adapting to various screen sizes, aspect ratios, and device orientations. The interface supports both portrait and landscape orientations, automatically adjusting layout and element sizing to maintain usability and readability across orientation changes.

The design prioritizes clarity and simplicity, emphasizing core tuning information (note name, meter, cent value) while keeping secondary controls (mode switching, settings) accessible without cluttering the display. Visual hierarchy ensures critical information remains prominent regardless of orientation or screen size.

**Priority:** CRITICAL  
**Stimulus/Response Sequences:**
1. User rotates device from portrait to landscape orientation
2. System detects orientation change event
3. System recalculates layout geometry and adjusts element positions
4. System redraws interface in new orientation within 200 ms
5. All functionality remains accessible and legible

**Functional Requirements:**

**FR-060: Portrait Orientation Support**  
**Priority:** CRITICAL  
The system shall support portrait (vertical) device orientation, providing fully functional interface with all features accessible and legible.

**FR-061: Landscape Orientation Support**  
**Priority:** CRITICAL  
The system shall support landscape (horizontal) device orientation, providing fully functional interface with all features accessible and legible.

**FR-062: Dynamic Orientation Switching**  
**Priority:** CRITICAL  
The system shall detect device orientation changes and update the user interface layout dynamically without interrupting audio processing, pitch detection, or tone generation.

**FR-063: Orientation Transition Performance**  
**Priority:** HIGH  
The system shall complete orientation change layout recalculation and redraw within 200 ms of receiving the orientation change event, ensuring smooth visual transition.

**FR-064: Layout Preservation During Orientation Change**  
**Priority:** HIGH  
The system shall preserve application state during orientation changes:
- Currently selected mode (Meter or Sound)
- Currently selected note (Sound Mode)
- Tone generation state (playing or stopped)
- Reference pitch setting
- No data loss or feature reset

**FR-065: Responsive Element Sizing**  
**Priority:** CRITICAL  
The system shall scale interface elements proportionally based on available screen dimensions, ensuring:
- Touch targets meet minimum platform sizes (44×44 points iOS, 48×48 dp Android)
- Text remains legible (minimum 12pt equivalent font size for body text)
- Tuning meter occupies appropriate proportion of screen (40-60% of vertical space in portrait)

**FR-066: Screen Size Adaptation**  
**Priority:** CRITICAL  
The system shall adapt layout to screen sizes ranging from:
- iOS: 4.7" diagonal (iPhone SE) to 6.7" diagonal (iPhone Pro Max)
- Android: 4.5" diagonal to 6.8" diagonal
- Aspect ratios: 16:9, 18:9, 19:9, 19.5:9, 20:9

**FR-067: Mode Selection Control**  
**Priority:** CRITICAL  
The system shall provide a mode selection control (segmented control, tabs, or toggle buttons) enabling users to switch between Meter Mode and Sound Mode with single tap interaction.

**FR-068: Mode Selection Visibility**  
**Priority:** HIGH  
The system shall display the mode selection control prominently near the top of the interface with clear labels ("Meter" and "Sound" or equivalent icons) and visual indication of the currently active mode.

**FR-069: Settings Access Control**  
**Priority:** HIGH  
The system shall provide a settings control (gear icon, menu button, or labeled button) positioned consistently in a corner or edge location, enabling access to reference pitch calibration and application information.

**FR-070: Help Access Control**  
**Priority:** MEDIUM  
The system should provide a help control (question mark icon or help button) enabling access to brief documentation explaining:
- Note names and octave numbers
- Cent deviation interpretation
- Pure interval reference marks
- Reference pitch calibration purpose
- Optimal usage conditions

**FR-071: Visual Hierarchy in Meter Mode**  
**Priority:** HIGH  
When in Meter Mode, the system shall prioritize visual prominence in descending order:
1. Tuning meter (largest element)
2. Note name and octave (second largest)
3. Cent deviation numeric value (third largest)
4. Flat/center/sharp indicators (integrated with meter)
5. Mode selection and settings controls (smallest, peripheral)

**FR-072: Visual Hierarchy in Sound Mode**  
**Priority:** HIGH  
When in Sound Mode, the system shall prioritize visual prominence in descending order:
1. Note selection interface (largest element)
2. Tone toggle control (large, prominent)
3. Selected note indication (clear visibility)
4. Mode selection and settings controls (smallest, peripheral)

**FR-073: Color Coding for Tuning Status**  
**Priority:** HIGH  
The system shall use color coding to communicate tuning status:
- Green zone or indicator: In tune (±5 cents)
- Yellow/orange zone: Slightly out of tune (5-20 cents deviation)
- Red zone: Significantly out of tune (>20 cents deviation)
- Colors shall be chosen to maintain accessibility for color vision deficiencies (avoid red-green only distinction)

**FR-074: Touch Target Spacing**  
**Priority:** HIGH  
The system shall maintain minimum spacing of 8 points (iOS) or 8 dp (Android) between adjacent touch targets to prevent accidental activation of wrong controls.

**FR-075: Safe Area Respect**  
**Priority:** CRITICAL  
The system shall respect platform-defined safe areas, avoiding placement of interactive controls or critical information in areas obscured by:
- iOS: Notches, Dynamic Island, home indicator
- Android: System navigation bars, camera cutouts, curved screen edges

**FR-076: Status Bar Handling**  
**Priority:** MEDIUM  
The system should hide the status bar (time, battery, signal indicators) when in full-screen use to maximize screen space for tuning interface, or use dark/light status bar style appropriate for background color.

**FR-077: System UI Integration**  
**Priority:** MEDIUM  
The system should follow platform design guidelines for:
- iOS: Navigation patterns, button styles, modal presentations
- Android: Material Design components, FAB patterns if applicable, bottom navigation if applicable

**FR-078: Minimum Contrast Ratio**  
**Priority:** HIGH  
The system shall ensure text and interactive elements maintain minimum contrast ratio of 4.5:1 against backgrounds (WCAG AA standard) for legibility in varied lighting conditions.

**FR-079: Font Scaling Support**  
**Priority:** MEDIUM  
The system should respect user-configured system font size preferences (iOS: Dynamic Type, Android: Font Scale) for text elements where feasible without compromising layout integrity.

**FR-080: Orientation Lock Option**  
**Priority:** LOW  
The system may provide an option to lock interface to portrait or landscape orientation based on user preference, preventing unwanted rotation during use.

**FR-081: Full Screen Focus Mode**  
**Priority:** LOW  
The system may provide an optional full-screen mode hiding all controls except core tuning display (note, meter, cent value) for distraction-free tuning focus.

**FR-082: Visual Feedback for Interactions**  
**Priority:** MEDIUM  
The system should provide immediate visual feedback for all touch interactions:
- Button press: Highlight or scale animation
- Toggle state change: Color or position transition
- Note selection: Selection highlight animation
- All feedback completing within 100 ms of touch event

---

### 3.5 System Feature: Audio Input/Output Management

#### 3.5.1 Description

Audio input/output management handles all interactions with platform audio subsystems, including microphone access for pitch detection, speaker output for tone generation, audio session configuration, permission handling, and resource management. This feature ensures reliable, low-latency audio processing while respecting platform policies, user privacy, and system resource constraints.

The system abstracts platform-specific audio API differences through JUCE framework while handling platform-specific requirements for permissions, audio routing, interruptions, and background behavior. Robust error handling ensures graceful degradation when audio resources are unavailable or restricted.

**Priority:** CRITICAL  
**Stimulus/Response Sequences:**
1. User launches application
2. System initializes JUCE audio device manager
3. System requests microphone permission if not previously granted
4. User grants permission
5. System opens audio input stream and begins monitoring
6. Audio processing proceeds with automatic handling of interruptions, route changes, and background transitions

**Functional Requirements:**

**FR-083: Microphone Permission Request**  
**Priority:** CRITICAL  
The system shall request microphone access permission on first launch or when permission status is "not determined", displaying platform-standard permission dialog with clear explanation: "Microphone access is required for pitch detection to analyze instrument sound and determine tuning accuracy."

**FR-084: Permission Status Detection**  
**Priority:** CRITICAL  
The system shall detect current microphone permission status on each launch and when returning from background:
- Granted: Proceed with audio initialization
- Denied: Display explanation and link to system settings
- Not determined: Request permission

**FR-085: Permission Denial Handling**  
**Priority:** CRITICAL  
When microphone permission is denied, the system shall:
- Display clear message explaining that Meter Mode requires microphone access
- Provide "Open Settings" button linking directly to application settings in system preferences
- Allow Sound Mode operation (tone generation) which does not require microphone
- Disable or gray out Meter Mode control until permission is granted

**FR-086: Audio Device Initialization**  
**Priority:** CRITICAL  
The system shall initialize JUCE AudioDeviceManager on application launch, configuring:
- Input channels: 1 (mono microphone)
- Output channels: 2 (stereo output)
- Sample rate: Device native rate (typically 44.1 kHz or 48 kHz)
- Buffer size: Minimum size supported by device for lowest latency, typically 256-512 samples

**FR-087: Sample Rate Adaptation**  
**Priority:** CRITICAL  
The system shall automatically adapt to the device's native audio sample rate without requiring specific rate, supporting common rates:
- 44.1 kHz (CD quality, common on iOS)
- 48 kHz (professional standard, common on Android)
- Other rates: 22.05 kHz, 96 kHz if device supports

All frequency calculations and autocorrelation parameters shall scale appropriately for active sample rate.

**FR-088: Buffer Size Optimization**  
**Priority:** HIGH  
The system shall request minimum available audio buffer size from the platform to minimize latency while avoiding buffer underruns:
- iOS: Typically 256 samples (~5.8 ms at 44.1 kHz)
- Android: Varies by device, typically 256-512 samples
- If device cannot support requested size, shall accept platform-determined alternative

**FR-089: Audio Callback Implementation**  
**Priority:** CRITICAL  
The system shall implement real-time audio callback processing:
- Meter Mode: Process input buffer for pitch detection within callback deadline
- Sound Mode: Generate output buffer with synthesized tone within callback deadline
- No memory allocation, file I/O, locks, or blocking operations within audio callback
- Thread priority: Real-time (highest priority) for audio thread

**FR-090: Input Level Monitoring**  
**Priority:** HIGH  
The system shall monitor microphone input level (peak amplitude) and detect:
- Signal presence: Input exceeding -40 dBFS threshold
- Clipping: Input approaching 0 dBFS indicating overload
- Silence: Input below threshold for >500 ms

**FR-091: Automatic Gain Control Handling**  
**Priority:** MEDIUM  
The system should disable automatic gain control (AGC) on platforms where controllable to prevent dynamic amplitude changes interfering with pitch detection algorithm confidence. If AGC cannot be disabled, algorithms shall accommodate amplitude variations.

**FR-092: Audio Route Detection**  
**Priority:** HIGH  
The system shall detect active audio routing:
- Built-in microphone and speaker
- Wired headset (microphone and headphones)
- Bluetooth headset
- External audio interface (if connected)

**FR-093: Audio Route Change Handling**  
**Priority:** HIGH  
The system shall handle audio route changes gracefully:
- Detect route change notification from platform
- Reconfigure audio session if necessary
- Continue pitch detection or tone generation on new route
- No application crash or audio dropout exceeding 100 ms

**FR-094: Audio Session Category Configuration**  
**Priority:** CRITICAL  
The system shall configure platform audio session categories appropriately:

iOS:
- Meter Mode: AVAudioSessionCategoryRecord (input only)
- Sound Mode: AVAudioSessionCategoryPlayback (output only)
- When switching modes: Update category accordingly

Android:
- Meter Mode: AudioManager.STREAM_MUSIC with recording enabled
- Sound Mode: AudioManager.USAGE_MEDIA

**FR-095: Audio Interruption Handling**  
**Priority:** CRITICAL  
The system shall handle audio interruptions gracefully:
- Incoming phone call: Pause audio processing, resume after call ends
- Alarm or notification: Continue processing if possible, or pause briefly
- Another app starting audio: Deactivate audio processing, display notification to user

**FR-096: Background Audio Suspension**  
**Priority:** CRITICAL  
The system shall automatically suspend all audio processing when application enters background state:
- Stop pitch detection in Meter Mode
- Stop tone generation in Sound Mode
- Release audio device resources to allow other applications access
- Do not attempt background audio processing (violates platform policies)

**FR-097: Foreground Audio Resumption**  
**Priority:** CRITICAL  
The system shall automatically resume audio processing when application returns to foreground:
- Reinitialize audio device if necessary
- Restore previous mode (Meter or Sound)
- Do not automatically reactivate tone if it was manually stopped
- Resume pitch detection monitoring in Meter Mode

**FR-098: Audio Device Error Handling**  
**Priority:** HIGH  
The system shall handle audio device errors gracefully:
- Device initialization failure: Display error message, allow retry
- Buffer underrun: Log occurrence, attempt to continue processing
- Device disconnection: Detect and attempt reconnection or fallback to built-in audio
- Excessive errors: Display notification suggesting device restart

**FR-099: CPU Load Monitoring**  
**Priority:** MEDIUM  
The system should monitor audio processing CPU load and:
- Log warning if audio callback exceeds 80% of available time budget
- Reduce processing complexity if sustained high load detected
- Display warning to user if device cannot maintain real-time performance

**FR-100: Sample Rate Conversion Prevention**  
**Priority:** HIGH  
The system shall avoid sample rate conversion by operating at device native rate, preventing:
- Added latency from resampling
- Audio quality degradation
- Increased CPU usage

**FR-101: Zero-Copy Audio Buffers**  
**Priority:** MEDIUM  
The system should minimize audio buffer copying where feasible:
- Process input directly from callback buffer
- Write output directly to callback buffer
- Avoid unnecessary intermediate buffers

**FR-102: Thread Priority Management**  
**Priority:** HIGH  
The system shall ensure audio processing thread runs at real-time priority to prevent preemption by lower-priority tasks that could cause dropouts or latency spikes.

**FR-103: Audio Focus Management (Android)**  
**Priority:** HIGH  
On Android, the system shall request and manage audio focus appropriately:
- Request audio focus when starting audio processing
- Release audio focus when stopping or backgrounding
- Handle audio focus loss notifications
- Duck or pause as appropriate for transient focus loss

**FR-104: Silent Mode Handling (iOS)**  
**Priority:** MEDIUM  
On iOS, the system should configure audio session to:
- Meter Mode: Record even when device in silent mode (microphone not affected by silent switch)
- Sound Mode: Play tones even when device in silent mode (using appropriate audio category)

**FR-105: Haptic Feedback for Audio Events**  
**Priority:** LOW  
The system may provide optional haptic feedback (vibration) for audio-related events:
- Pitch detection achieves "in tune" status
- Tone generation starts/stops
- Configurable in settings, disabled by default

---

## 4. Data Requirements

### 4.1 Logical Data Model

The Chromatic Tuner application maintains minimal persistent data, focusing primarily on user preferences and configuration. The logical data model consists of a single entity with no complex relationships, reflecting the application's simple, offline-only architecture.

#### 4.1.1 Entity-Relationship Overview

```
┌─────────────────────────────────────┐
│      ApplicationConfiguration       │
│                                     │
│  - referencePitchHz : Integer       │
│  - orientationLock : Enumeration    │
│  - lastUsedMode : Enumeration       │
│  - configVersion : Integer          │
│                                     │
└─────────────────────────────────────┘
```

**Entity: ApplicationConfiguration**

This entity represents the complete set of user preferences and configuration settings persisted across application sessions. The entity is implemented as a flat key-value structure using platform-provided storage mechanisms rather than a relational database.

**Primary Key:** None required (single instance, not a collection)

**Attributes:**

| Attribute | Data Type | Constraints | Description |
|-----------|-----------|-------------|-------------|
| referencePitchHz | Integer | Range: 410-480<br>Default: 440<br>Required | A4 reference pitch frequency in Hertz used for all pitch calculations |
| orientationLock | Enumeration | Values: NONE, PORTRAIT, LANDSCAPE<br>Default: NONE<br>Optional | User preference for orientation locking (future enhancement) |
| lastUsedMode | Enumeration | Values: METER, SOUND<br>Default: METER<br>Optional | Last active mode for potential restoration on launch (future enhancement) |
| configVersion | Integer | Min: 1<br>Default: 1<br>Required | Schema version for future migration compatibility |

**Relationships:** None (single independent entity)

**Cardinality:** 1 (exactly one configuration instance per application installation)

#### 4.1.2 Transient Runtime Data

The following data structures exist only in memory during application execution and are not persisted:

**DetectedPitchData (Runtime Structure)**
```
{
  fundamentalFrequency: Float (Hz)
  confidence: Float (0.0-1.0)
  noteName: String (C, C#, D, ..., B)
  octaveNumber: Integer (1-8)
  centDeviation: Float (-50.0 to +50.0)
  signalLevel: Float (dBFS)
  timestamp: TimePoint
}
```

**AudioBufferData (Runtime Structure)**
```
{
  inputBuffer: Float[] (sample data)
  outputBuffer: Float[] (sample data)
  bufferSize: Integer (samples)
  sampleRate: Integer (Hz)
  timestamp: TimePoint
}
```

**UIStateData (Runtime Structure)**
```
{
  currentMode: Enumeration (METER, SOUND)
  selectedNote: Enumeration (C4, C#4, ..., C5)
  toneGenerationActive: Boolean
  displayOrientation: Enumeration (PORTRAIT, LANDSCAPE)
  permissionStatus: Enumeration (GRANTED, DENIED, NOT_DETERMINED)
}
```

These runtime structures are recalculated or reset on each application launch and are not stored persistently.

### 4.2 Data Dictionary

#### 4.2.1 Persistent Data Elements

**DR-001: referencePitchHz**
- **Description:** The A4 reference pitch frequency that serves as the tuning standard for all pitch detection and tone generation calculations
- **Data Type:** Integer (16-bit unsigned)
- **Valid Range:** 410-480 inclusive
- **Units:** Hertz (Hz)
- **Default Value:** 440
- **Storage Key:** "com.chromatictuner.referencePitch" or equivalent platform-specific identifier
- **Update Frequency:** On-demand when user modifies calibration setting
- **Validation Rules:** Must be integer value within range; values outside range shall be clamped or rejected
- **Usage Context:** Read on application launch and when user accesses calibration interface; written when user modifies setting
- **Dependencies:** Affects all frequency calculations in both Meter Mode and Sound Mode

**DR-002: orientationLock**
- **Description:** User preference for device orientation locking behavior (future enhancement)
- **Data Type:** Enumeration (stored as integer or string)
- **Valid Values:**
  - 0 or "NONE": No lock, support both portrait and landscape (default)
  - 1 or "PORTRAIT": Lock to portrait orientation only
  - 2 or "LANDSCAPE": Lock to landscape orientation only
- **Default Value:** 0 or "NONE"
- **Storage Key:** "com.chromatictuner.orientationLock"
- **Update Frequency:** On-demand when user modifies settings
- **Validation Rules:** Must match one of three valid values; invalid values default to NONE
- **Usage Context:** Version 1.0 does not implement this preference; defined for future compatibility
- **Dependencies:** None in Version 1.0

**DR-003: lastUsedMode**
- **Description:** The mode (Meter or Sound) the user was last using before closing the application (future enhancement for state restoration)
- **Data Type:** Enumeration (stored as integer or string)
- **Valid Values:**
  - 0 or "METER": Meter Mode (pitch detection)
  - 1 or "SOUND": Sound Mode (tone generation)
- **Default Value:** 0 or "METER"
- **Storage Key:** "com.chromatictuner.lastMode"
- **Update Frequency:** On application termination or backgrounding
- **Validation Rules:** Must match one of two valid values; invalid values default to METER
- **Usage Context:** Version 1.0 does not restore last mode; always starts in Meter Mode; defined for future enhancement
- **Dependencies:** None in Version 1.0

**DR-004: configVersion**
- **Description:** Schema version number for configuration data structure, enabling future migration of settings when data model changes
- **Data Type:** Integer (16-bit unsigned)
- **Valid Range:** 1-65535
- **Default Value:** 1
- **Storage Key:** "com.chromatictuner.configVersion"
- **Update Frequency:** Only when application updates modify data schema
- **Validation Rules:** Must be positive integer; missing value treated as version 1
- **Usage Context:** Read on application launch to determine if migration needed; written when schema changes are applied
- **Dependencies:** Controls interpretation of other stored values

#### 4.2.2 Runtime Data Elements

**DR-005: fundamentalFrequency**
- **Description:** The detected fundamental frequency of audio input in Hertz
- **Data Type:** Float (32-bit IEEE 754)
- **Valid Range:** 32.70-4186.01 Hz (C1 to C8)
- **Units:** Hertz (Hz)
- **Precision:** 0.1 Hz minimum resolution
- **Update Frequency:** Continuous during pitch detection (20+ Hz update rate)
- **Lifetime:** Transient; exists only during active pitch detection
- **Usage Context:** Meter Mode pitch detection calculations
- **Dependencies:** Input audio buffer data, autocorrelation analysis results

**DR-006: confidence**
- **Description:** Statistical confidence level of pitch detection result, ranging from 0.0 (no confidence) to 1.0 (maximum confidence)
- **Data Type:** Float (32-bit IEEE 754)
- **Valid Range:** 0.0-1.0
- **Units:** Unitless (normalized probability)
- **Update Frequency:** Continuous during pitch detection
- **Lifetime:** Transient; recalculated with each analysis frame
- **Usage Context:** Determines whether to display detection result or show "no signal" state
- **Dependencies:** NSDF peak analysis, autocorrelation clarity

**DR-007: noteName**
- **Description:** The chromatic note name of detected or selected pitch
- **Data Type:** String or Enumeration
- **Valid Values:** C, C#, D, D#, E, F, F#, G, G#, A, A#, B
- **Character Encoding:** ASCII (7-bit)
- **String Length:** 1-2 characters
- **Update Frequency:** Meter Mode: Continuous during detection; Sound Mode: On user selection
- **Lifetime:** Transient during detection; persists for selected note in Sound Mode during session
- **Usage Context:** Display of detected note (Meter Mode) or selected reference note (Sound Mode)
- **Dependencies:** Fundamental frequency, reference pitch setting

**DR-008: octaveNumber**
- **Description:** The octave number using scientific pitch notation (C4 = middle C)
- **Data Type:** Integer (8-bit signed)
- **Valid Range:** 1-8
- **Update Frequency:** Continuous during pitch detection in Meter Mode
- **Lifetime:** Transient; recalculated with each detection
- **Usage Context:** Display of complete note designation (e.g., "A4", "C#3")
- **Dependencies:** Fundamental frequency, note name

**DR-009: centDeviation**
- **Description:** The pitch deviation from target note frequency measured in cents
- **Data Type:** Float (32-bit IEEE 754)
- **Valid Range:** -50.0 to +50.0 cents (display range; calculations may exceed)
- **Units:** Cents (100 cents = 1 semitone)
- **Precision:** 0.1 cent display precision
- **Update Frequency:** Continuous during pitch detection (20+ Hz)
- **Lifetime:** Transient; recalculated with each analysis frame
- **Usage Context:** Numeric display and tuning meter needle position in Meter Mode
- **Dependencies:** Fundamental frequency, target note frequency, reference pitch
- **Calculation Formula:** `1200 × log₂(f_detected / f_target)`

**DR-010: signalLevel**
- **Description:** The peak amplitude of audio input signal
- **Data Type:** Float (32-bit IEEE 754)
- **Valid Range:** -∞ to 0.0 dBFS (decibels full scale)
- **Units:** dBFS (decibels relative to full scale)
- **Update Frequency:** Continuous during audio input processing
- **Lifetime:** Transient; updated with each audio buffer
- **Usage Context:** Threshold detection for signal presence vs. noise
- **Dependencies:** Input audio buffer data
- **Threshold Value:** -40 dBFS minimum for valid signal

**DR-011: selectedNote**
- **Description:** The note selected by user in Sound Mode for reference tone generation
- **Data Type:** Enumeration
- **Valid Values:** C4, C#4, D4, D#4, E4, F4, F#4, G4, G#4, A4, A#4, B4, C5 (13 values)
- **Default Value:** A4 (440 Hz at default reference pitch)
- **Update Frequency:** On user interaction with note selection interface
- **Lifetime:** Session; resets to default on application restart
- **Usage Context:** Determines frequency of generated reference tone in Sound Mode
- **Dependencies:** Reference pitch setting

**DR-012: toneGenerationActive**
- **Description:** Boolean flag indicating whether reference tone is currently being generated
- **Data Type:** Boolean
- **Valid Values:** true (tone playing), false (tone stopped)
- **Default Value:** false
- **Update Frequency:** On toggle control interaction
- **Lifetime:** Session; resets to false on application restart or backgrounding
- **Usage Context:** Controls tone synthesis in Sound Mode, determines toggle control visual state
- **Dependencies:** Audio output state, Sound Mode activation

**DR-013: currentMode**
- **Description:** The currently active operating mode
- **Data Type:** Enumeration
- **Valid Values:** METER (pitch detection), SOUND (tone generation)
- **Default Value:** METER
- **Update Frequency:** On mode selection control interaction
- **Lifetime:** Session; resets to METER on application restart
- **Usage Context:** Determines which UI and audio processing is active
- **Dependencies:** Mode selection control state

**DR-014: audioBuffers**
- **Description:** Real-time audio input/output buffers containing sample data
- **Data Type:** Arrays of Float (32-bit IEEE 754)
- **Buffer Sizes:** Typically 256-512 samples per channel
- **Sample Rate:** 44.1 kHz or 48 kHz (device-dependent)
- **Update Frequency:** Continuous at audio callback rate (~100-200 Hz depending on buffer size)
- **Lifetime:** Immediate; overwritten with each audio callback
- **Usage Context:** Input buffer for pitch detection analysis; output buffer for tone synthesis
- **Dependencies:** Audio device initialization, platform audio system

#### 4.2.3 Calculated Data Elements

**DR-015: targetFrequency**
- **Description:** The ideal frequency for a given note based on current reference pitch and 12-tone equal temperament
- **Data Type:** Float (64-bit IEEE 754 for precision in calculation)
- **Valid Range:** 32.70-4186.01 Hz (covering C1 to C8)
- **Units:** Hertz (Hz)
- **Calculation Frequency:** On-demand when note frequency needed; cached per reference pitch value
- **Lifetime:** Cached until reference pitch changes
- **Calculation Formula:** `f_A4 × 2^((n - 57) / 12)` where n is MIDI note number
- **Usage Context:** Cent deviation calculation, tone generation frequency
- **Dependencies:** Reference pitch setting, note name, octave number
- **Precision:** Sufficient to achieve ±1.5 cent output accuracy (requires ~0.05 Hz precision)

**DR-016: meterNeedlePosition**
- **Description:** Visual position of tuning meter needle as percentage of meter range
- **Data Type:** Float (32-bit IEEE 754)
- **Valid Range:** 0.0-1.0 (representing -50 to +50 cent range)
- **Units:** Normalized position (0.5 = center)
- **Update Frequency:** Continuous during pitch detection (30+ FPS)
- **Lifetime:** Transient; recalculated for each display frame
- **Calculation Formula:** `0.5 + (centDeviation / 100.0)` with clamping to 0.0-1.0 range
- **Usage Context:** Visual rendering of tuning meter needle
- **Dependencies:** Cent deviation, display update cycle

### 4.3 Reports

The Chromatic Tuner application does not generate formal reports or exportable documents. However, the following informational displays provide data output to users:

**INF-001: Tuning Status Display (Meter Mode)**
- **Purpose:** Communicate current tuning status to user during pitch detection
- **Content:**
  - Detected note name and octave (e.g., "A4")
  - Cent deviation numeric value (e.g., "-12.3")
  - Tuning meter visual representation
  - Flat/center/sharp indicator status
- **Update Frequency:** Real-time (20-30 Hz)
- **Format:** Visual on-screen display
- **Persistence:** None; transient display only
- **Export Capability:** None

**INF-002: Reference Tone Status Display (Sound Mode)**
- **Purpose:** Confirm which reference tone is selected and whether it is currently playing
- **Content:**
  - Selected note name and octave (e.g., "A4")
  - Tone generation status (playing/stopped)
  - Current reference pitch setting (e.g., "440 Hz")
- **Update Frequency:** On state change
- **Format:** Visual on-screen display
- **Persistence:** None; transient display only
- **Export Capability:** None

**INF-003: Configuration Display (Settings Screen)**
- **Purpose:** Show current application configuration to user
- **Content:**
  - Current reference pitch value (e.g., "440 Hz")
  - Valid range indication (410-480 Hz)
  - Application version number
  - Platform information (iOS/Android version)
- **Update Frequency:** On settings screen display or configuration change
- **Format:** Visual on-screen display
- **Persistence:** None; transient display only
- **Export Capability:** None

**INF-004: Help Information Display**
- **Purpose:** Provide educational information to users
- **Content:**
  - Note name explanations (chromatic scale)
  - Cent deviation concept explanation
  - Pure interval reference mark descriptions
  - Optimal usage conditions guidance
  - Reference pitch calibration explanation
- **Update Frequency:** On-demand when user accesses help
- **Format:** Visual on-screen display (text with optional diagrams)
- **Persistence:** Static content embedded in application
- **Export Capability:** None

**Future Report Considerations (Out of Scope for Version 1.0):**
- Tuning history log with timestamp, detected notes, and cent deviations
- Tuning session statistics (time in tune, average deviation, notes detected)
- Exportable tuning data in CSV or JSON format for analysis
- Practice session summaries

### 4.4 Data Acquisition, Integrity, Retention and Disposal

#### 4.4.1 Data Acquisition

**ACQ-001: Reference Pitch Configuration**
- **Source:** Direct user input via calibration interface
- **Acquisition Method:** User adjusts increment/decrement controls or enters numeric value
- **Validation:** Range check (410-480 Hz), integer rounding if fractional value entered
- **Frequency:** On-demand when user modifies setting
- **Error Handling:** Invalid values clamped to range limits; display validation message
- **Initial Acquisition:** Default value (440 Hz) on first application launch

**ACQ-002: Microphone Audio Input**
- **Source:** Device microphone or connected audio input hardware
- **Acquisition Method:** Platform audio API callbacks providing sample buffers
- **Validation:** Range check (verify samples within -1.0 to +1.0 normalized range), detect clipping
- **Frequency:** Continuous at audio sample rate (44.1/48 kHz)
- **Error Handling:** Buffer underrun detection, device error recovery, permission denial handling
- **Quality Assurance:** Minimum signal threshold (-40 dBFS) to reject noise-floor data

**ACQ-003: User Interaction Events**
- **Source:** Touchscreen events from platform UI system
- **Acquisition Method:** Platform touch event handlers
- **Validation:** Touch target boundary checking, gesture recognition
- **Frequency:** On-demand when user interacts with interface
- **Error Handling:** Ignore touches outside valid target areas; reject ambiguous gestures

**ACQ-004: Device Orientation Data**
- **Source:** Platform device orientation sensors and UI system
- **Acquisition Method:** Platform orientation change notifications
- **Validation:** Verify orientation is supported (portrait or landscape)
- **Frequency:** On orientation change events (typically <1 Hz)
- **Error Handling:** Maintain current orientation if new orientation unsupported

#### 4.4.2 Data Integrity

**INT-001: Persistent Data Integrity**
- **Protection Mechanism:** Platform-provided atomic write operations for UserDefaults (iOS) / SharedPreferences (Android)
- **Validation on Read:** Range validation, type checking, default substitution for corrupted values
- **Corruption Detection:** Check for out-of-range values, null/undefined values, incorrect data types
- **Recovery Strategy:** Revert to default values if corruption detected; log occurrence for debugging
- **Backup:** No explicit backup; platform handles storage reliability

**INT-002: Runtime Data Consistency**
- **Synchronization:** Reference pitch changes trigger immediate recalculation of all dependent frequency values
- **Thread Safety:** Audio thread data protected from concurrent modification by UI thread using atomic operations or lock-free structures
- **State Coherency:** Mode transitions ensure clean state changes (e.g., tone stops when switching to Meter Mode)
- **Validation:** Range checks on all calculated values; sanity checks on frequency ratios

**INT-003: Audio Data Integrity**
- **Sample Validity:** Verify audio samples within normalized range (-1.0 to +1.0); clip if exceeded
- **Buffer Completeness:** Detect partial buffer delivery; request buffer resend or skip frame
- **Timestamp Continuity:** Monitor for gaps in audio timeline indicating dropouts
- **Glitch Prevention:** Apply fade-in/fade-out envelopes to prevent clicks from abrupt starts/stops

**INT-004: Calculation Precision**
- **Floating-Point Accuracy:** Use double-precision (64-bit) for intermediate frequency calculations; single-precision (32-bit) acceptable for display values
- **Rounding Control:** Explicit rounding rules for cent display (0.1 cent precision) and reference pitch (integer Hz)
- **Range Clamping:** Clamp displayed cent values to ±50 range even if internal calculation exceeds
- **Overflow Prevention:** Validate inputs before logarithmic and exponential calculations to prevent NaN or infinity results

#### 4.4.3 Data Retention

**RET-001: Persistent Configuration Retention**
- **Retention Duration:** Indefinite until user uninstalls application or manually resets settings
- **Storage Location:** Platform-standard user preferences storage (iOS: UserDefaults in app sandbox, Android: SharedPreferences in app data directory)
- **Retention Policy:** No automatic expiration; survives application updates
- **User Control:** User may reset to defaults manually; platform provides app data clearing option
- **Platform Behavior:** iOS/Android preserve user preferences across app updates but delete on uninstall

**RET-002: Runtime Data Retention**
- **Retention Duration:** Session only; all runtime data discarded on application termination
- **Storage Location:** Application memory (heap, stack)
- **Retention Policy:** No persistence; recalculated on each launch
- **Exception:** User may expect tone generation state to persist within session but not across launches

**RET-003: Audio Buffer Retention**
- **Retention Duration:** Immediate; overwritten with each audio callback (every 5-10 ms)
- **Storage Location:** Audio thread stack or pre-allocated buffers
- **Retention Policy:** No retention; immediately overwritten and no recording occurs
- **Security Consideration:** Ensures microphone data not persisted, addressing privacy concerns

**RET-004: Diagnostic Data Retention (Platform Crash Reports)**
- **Retention Duration:** Platform-determined (typically 30 days on device, variable in platform analytics)
- **Storage Location:** Platform crash reporting system (opt-in by user)
- **Retention Policy:** Platform-controlled; application has no direct access
- **User Control:** Users may disable crash reporting in device settings
- **Data Content:** Stack traces, device model, OS version; no audio data or user content

#### 4.4.4 Data Disposal

**DIS-001: Session Data Disposal**
- **Trigger:** Application termination, backgrounding, or mode switch
- **Method:** Automatic memory deallocation by platform runtime
- **Verification:** No verification needed; runtime handles garbage collection or reference counting
- **Scope:** All runtime data structures, audio buffers, detection results, UI state

**DIS-002: Persistent Configuration Disposal**
- **Trigger:** User uninstalls application or explicitly clears app data through platform settings
- **Method:** Platform deletes app sandbox including all stored preferences
- **Verification:** Platform guarantees complete removal
- **User Control:** User initiates via platform settings or app uninstall
- **Recovery:** No recovery possible after disposal; reinstall uses default values

**DIS-003: Audio Data Disposal**
- **Trigger:** Immediate after processing (within audio callback cycle)
- **Method:** Buffer overwrite with new audio data; no explicit clearing needed
- **Verification:** No retention to verify; immediate overwrite prevents persistence
- **Privacy Assurance:** Microphone data never persisted to storage, ensuring privacy

**DIS-004: Cached Calculation Disposal**
- **Trigger:** Reference pitch change invalidates cached frequency calculations
- **Method:** Cache invalidation flags or immediate recalculation
- **Verification:** Test that cent deviation updates correctly after reference pitch change
- **Scope:** Cached target frequencies, lookup tables, pre-calculated values

**DIS-005: Memory Cleanup on Low Memory Warning**
- **Trigger:** Platform low-memory warning notification
- **Method:** Release non-essential cached data, reduce buffer allocations if possible
- **Verification:** Application remains functional after cleanup
- **Priority:** Preserve audio processing capability; release UI-related caches first
- **Recovery:** Reallocate resources when memory available

#### 4.4.5 Privacy and Data Protection

**PRIV-001: No Personal Data Collection**
- **Policy:** Application collects no personally identifiable information (PII)
- **Enforcement:** No network communication, no user accounts, no analytics beyond platform-standard opt-in crash reporting
- **Verification:** Code review confirms no data transmission functions; network security audit

**PRIV-002: Microphone Data Usage**
- **Policy:** Microphone data used exclusively for real-time pitch detection; never recorded, stored, or transmitted
- **Enforcement:** No file I/O operations on audio buffers; no network transmission of audio data
- **User Notification:** Permission dialog clearly states microphone usage purpose
- **Verification:** Code audit confirms no audio recording functions

**PRIV-003: Local-Only Storage**
- **Policy:** All data stored locally on device; no cloud synchronization or remote storage
- **Enforcement:** No network access permission requested; application functions without network
- **User Benefit:** Complete offline operation; no data exposure through network transmission
- **Verification:** Network activity monitoring confirms zero network usage

**PRIV-004: Data Minimization**
- **Policy:** Store only essential user preference (reference pitch); avoid collecting unnecessary data
- **Rationale:** Privacy by design; reduces privacy risk and simplifies compliance
- **Implementation:** Single integer value stored; no usage tracking, analytics, or telemetry
- **Compliance:** Exceeds GDPR/CCPA minimization requirements through near-zero data collection

**PRIV-005: User Control and Transparency**
- **Control:** User controls reference pitch setting; may reset to default at any time
- **Transparency:** Help documentation and app store description clearly state offline-only operation and minimal data storage
- **Deletion:** User may delete all application data via platform settings or uninstall
- **Consent:** Microphone permission request with clear explanation; user grants explicit consent

---

## 5. External Interface Requirements

This section defines all interfaces between the Chromatic Tuner application and external entities including users, hardware components, software systems, and communication channels.

### 5.1 User Interfaces

#### 5.1.1 General User Interface Characteristics

**UI-001: Touch-First Design Philosophy**  
**Priority:** CRITICAL  
The user interface shall be designed primarily for touch interaction on mobile devices, with all interactive elements optimized for finger-based input rather than mouse/pointer precision.

**UI-002: Platform-Appropriate Visual Design**  
**Priority:** HIGH  
The user interface shall follow platform-specific design conventions while maintaining functional consistency:
- **iOS:** Follow iOS Human Interface Guidelines including SF Symbols for icons, system fonts, rounded corners, blur effects
- **Android:** Follow Material Design 3 principles including Material icons, Roboto font family, elevation, ripple effects

**UI-003: Color Palette**  
**Priority:** HIGH  
The user interface shall employ a consistent color palette:
- **Background:** Light neutral (white, light gray #F5F5F5)
- **Primary accent:** Tuner brand color (recommendation: blue #2196F3 or music-related hue)
- **Status indicators:**
  - In tune (center): Green #4CAF50
  - Slightly out of tune: Yellow/amber #FFC107
  - Significantly out of tune: Orange #FF9800 or red #F44336
- **Text:** Dark gray #212121 for primary, medium gray #757575 for secondary
- **Contrast:** All color combinations shall meet WCAG AA contrast ratio minimum 4.5:1

**UI-004: Typography**  
**Priority:** MEDIUM  
The user interface shall use legible typography with appropriate sizing:
- **Platform fonts:** San Francisco (iOS), Roboto (Android)
- **Note name display:** 48-72 pt (scalable based on screen size)
- **Cent value display:** 24-36 pt
- **Button labels:** 16-18 pt
- **Body text (help):** 14-16 pt
- **Font weights:** Regular for body, Medium/Semibold for emphasis, Bold for note names

**UI-005: Touch Target Sizes**  
**Priority:** CRITICAL  
All interactive elements shall meet minimum touch target dimensions:
- **iOS:** 44×44 points minimum
- **Android:** 48×48 dp minimum
- **Recommended:** 56×56 dp for primary actions
- **Spacing:** Minimum 8 pt/dp between adjacent touch targets

#### 5.1.2 Main Screen Layout (Meter Mode)

**UI-006: Meter Mode Screen Composition**  
**Priority:** CRITICAL  
The Meter Mode screen shall contain the following elements in visual hierarchy order:

1. **Status Bar Area** (top)
   - Mode selector (segmented control or tabs): "Meter" | "Sound"
   - Settings button (gear icon, top-right corner)
   - Help button (question mark icon, optional top-left)

2. **Primary Display Area** (center, ~60% of screen height)
   - Note name and octave display (large text, centered)
   - Octave number (smaller, adjacent or subscript to note)
   - Cent deviation numeric value (medium text, below note)

3. **Tuning Meter Area** (~30% of screen height)
   - Analog-style arc meter (120-180 degree arc)
   - Cent scale markings (-50, -40, -30, -20, -10, 0, +10, +20, +30, +40, +50)
   - Animated needle indicating current deviation
   - Colored zones (flat: left, center: middle, sharp: right)
   - Pure interval reference marks at -13.7 and +15.6 cents

4. **Status Indicator Area** (bottom)
   - Text indicators: "FLAT" | "IN TUNE" | "SHARP"
   - Optional: Visual symbols (arrows or color blocks)

**UI-007: Meter Mode Portrait Layout**  
**Priority:** CRITICAL  
In portrait orientation, elements shall stack vertically:
```
┌─────────────────────────┐
│ [Meter] [Sound]    [⚙️] │ ← Mode selector + settings
├─────────────────────────┤
│                         │
│         A4              │ ← Note name (large)
│                         │
│      -12.3 cents        │ ← Cent value
│                         │
├─────────────────────────┤
│   ╱─────┬─────╲        │
│  ╱  F   │C   S  ╲      │ ← Tuning meter arc
│ │       ▲       │      │ ← Needle
│  ╲  -50  0  +50 ╱      │
│   ╲─────┴─────╱        │
├─────────────────────────┤
│       FLAT              │ ← Status indicator
└─────────────────────────┘
```

**UI-008: Meter Mode Landscape Layout**  
**Priority:** CRITICAL  
In landscape orientation, elements shall distribute horizontally to utilize width:
```
┌──────────────────────────────────────────┐
│ [Meter][Sound]              [⚙️]         │
├──────────────────────────────────────────┤
│                                          │
│    A4          ╱─────┬─────╲           │
│              ╱   F   │C   S  ╲          │
│  -12.3¢     │        ▲       │          │
│              ╲  -50  0  +50 ╱           │
│    FLAT       ╲─────┴─────╱            │
│                                          │
└──────────────────────────────────────────┘
```

**UI-009: Tuning Meter Visual Design**  
**Priority:** CRITICAL  
The tuning meter shall be rendered as follows:
- **Arc geometry:** Semicircular or semi-elliptical arc spanning 120-180 degrees
- **Needle:** Thin line (2-3 pt width) extending from arc center to current position on arc
- **Needle animation:** Smooth interpolation with damping factor 0.7-0.85 to reduce jitter
- **Scale markings:** Small tick marks at 10-cent intervals, larger at 25-cent intervals, largest at 0 (center)
- **Zone colors:** Gradient or solid fills:
  - -50 to -5: Red/orange gradient fading to transparent
  - -5 to +5: Green solid or gradient
  - +5 to +50: Orange/red gradient fading from transparent
- **Pure interval marks:** Small triangular markers or dots at -13.7 and +15.6 cents

**UI-010: Note Name Display Format**  
**Priority:** CRITICAL  
Note names shall be displayed using the following format:
- **Sharp notation:** Use "#" symbol (e.g., "C#", "F#", "G#")
- **No flat notation:** Display only sharp equivalents (D# not Eb, A# not Bb)
- **Octave:** Subscript or adjacent smaller text (e.g., "A₄" or "A 4")
- **Color:** High contrast against background
- **Alignment:** Centered horizontally

**UI-011: Cent Value Display Format**  
**Priority:** HIGH  
Cent deviation values shall be displayed as:
- **Sign:** Always show "+" for positive, "-" for negative, "±" or nothing for exactly 0.0
- **Precision:** One decimal place (e.g., "-12.3", "+5.7", "0.0")
- **Units:** Display "cents" or "¢" symbol adjacent to value
- **Color coding:** Optional color matching zone (green when |cents| ≤ 5)

**UI-012: No Signal State Display**  
**Priority:** HIGH  
When no valid pitch is detected, the interface shall display:
- Note name: "–" or "∙∙∙" (em dash or ellipsis)
- Cent value: "–.–" or hidden
- Meter needle: Centered at 0 or hidden
- Status: "No Signal" or equivalent message
- Optional: Microphone icon with indication to play instrument

#### 5.1.3 Sound Mode Screen Layout

**UI-013: Sound Mode Screen Composition**  
**Priority:** CRITICAL  
The Sound Mode screen shall contain:

1. **Status Bar Area** (top, identical to Meter Mode)
   - Mode selector: "Meter" | "Sound" (Sound highlighted)
   - Settings button

2. **Reference Pitch Display** (top-center)
   - Current reference pitch: "A4 = 440 Hz" (medium text)

3. **Note Selection Interface** (center, ~50% of screen)
   - Visual keyboard or button grid showing C4 through C5
   - 13 notes: C, C#, D, D#, E, F, F#, G, G#, A, A#, B, C (one octave)
   - Selected note visually highlighted

4. **Tone Control Area** (bottom, ~20% of screen)
   - Large toggle button: "Play Tone" / "Stop Tone"
   - Button state clearly indicates active/inactive

**UI-014: Note Selection Visual Keyboard**  
**Priority:** HIGH  
The note selection interface shall resemble a piano keyboard layout:
- White keys (C, D, E, F, G, A, B, C): Larger rectangular buttons
- Black keys (C#, D#, F#, G#, A#): Smaller buttons positioned above and between white keys
- Each key labeled with note name
- Selected key highlighted with color, border, or elevation
- Touch feedback on tap (ripple effect or brief color change)

**UI-015: Alternative Note Selection Grid**  
**Priority:** MEDIUM  
As an alternative to keyboard layout, may provide grid layout:
- 13 equal-sized buttons in 2 rows
- Row 1: C4, C#4, D4, D#4, E4, F4, F#4
- Row 2: G4, G#4, A4, A#4, B4, C5
- Each button labeled with note name and octave
- Selected button highlighted

**UI-016: Sound Mode Tone Toggle Button**  
**Priority:** CRITICAL  
The tone toggle button shall:
- **Size:** Large (minimum 60×60 dp), occupying significant bottom screen area
- **Inactive state:** Label "Play Tone" or "▶" symbol, neutral color
- **Active state:** Label "Stop Tone" or "■" symbol, accent color indicating active
- **Visual feedback:** Immediate color/icon change on tap
- **Animation:** Optional pulsing or waveform animation when tone playing

**UI-017: Sound Mode Portrait Layout**  
**Priority:** CRITICAL  
```
┌─────────────────────────┐
│ [Meter] [Sound]    [⚙️] │
├─────────────────────────┤
│    A4 = 440 Hz          │ ← Reference pitch
├─────────────────────────┤
│                         │
│  ┌───┬─┬───┬─┬───┬───┐ │
│  │ C │#│ D │#│ E │ F │ │ ← Virtual keyboard
│  └───┴─┴───┴─┴───┴───┘ │    (simplified view)
│  ┌─┬───┬─┬───┬─┬───┬─┐ │
│  │#│ G │#│ A │#│ B │C│ │
│  └─┴───┴─┴───┴─┴───┴─┘ │
│                         │
├─────────────────────────┤
│    ┌─────────────┐     │
│    │  Play Tone  │     │ ← Toggle button
│    └─────────────┘     │
└─────────────────────────┘
```

#### 5.1.4 Settings Screen

**UI-018: Settings Screen Composition**  
**Priority:** HIGH  
The settings screen shall provide:

1. **Navigation**
   - Back button or close "X" to return to main screen
   - Title: "Settings" or "Calibration"

2. **Reference Pitch Section**
   - Label: "Reference Pitch (A4)"
   - Current value display: "440 Hz" (large, centered)
   - Decrement button: "–" or "▼"
   - Increment button: "+" or "▲"
   - Optional: Slider or picker for faster adjustment
   - Range indicator: "410 - 480 Hz"
   - Reset button: "Reset to 440 Hz"

3. **About Section** (optional)
   - Application name and version
   - Copyright information
   - Credits/acknowledgments
   - Privacy policy link (if applicable)

**UI-019: Reference Pitch Adjustment Controls**  
**Priority:** CRITICAL  
```
┌─────────────────────────┐
│  ← Settings             │
├─────────────────────────┤
│  Reference Pitch (A4)   │
│                         │
│    [–]   440 Hz   [+]   │ ← Inc/dec buttons
│                         │
│  Range: 410 - 480 Hz    │
│                         │
│  ┌───────────────────┐  │
│  │ Reset to 440 Hz   │  │
│  └───────────────────┘  │
└─────────────────────────┘
```

**UI-020: Settings Stepper Control**  
**Priority:** HIGH  
The increment/decrement controls shall:
- **Button size:** Minimum 44×44 pt (iOS) / 48×48 dp (Android)
- **Positioning:** Flanking the current value display
- **Repeat behavior:** Long-press continues incrementing/decrementing
- **Bounds:** Stop at 410 Hz (decrement) and 480 Hz (increment)
- **Visual feedback:** Highlight on touch, disable appearance when at bounds

#### 5.1.5 Help Screen

**UI-021: Help Screen Content**  
**Priority:** MEDIUM  
The help screen shall provide concise explanations:

1. **Chromatic Scale Reference**
   - Table or diagram showing: C, C#, D, D#, E, F, F#, G, G#, A, A#, B
   - Explanation: "All twelve notes used in Western music"

2. **Cents Explanation**
   - Definition: "Unit measuring pitch difference; 100 cents = 1 semitone"
   - Usage: "0 cents = perfect tune; negative = flat; positive = sharp"

3. **Pure Interval Marks Explanation**
   - "Markers at -13.7¢ and +15.6¢ show pure thirds for reference"
   - Brief historical context (optional)

4. **Reference Pitch Explanation**
   - "A4 reference pitch sets tuning standard (default 440 Hz)"
   - Common alternatives: 442 Hz (orchestra), 432 Hz (alternative)

5. **Usage Tips**
   - "Use in quiet environment for best accuracy"
   - "Hold note steadily for stable reading"
   - "Position device 30-100 cm from instrument"

**UI-022: Help Screen Format**  
**Priority:** LOW  
- Scrollable text with section headers
- Optional: Expandable/collapsible sections
- Inline diagrams or illustrations
- Back/close button to return to main screen

#### 5.1.6 Accessibility Considerations

**UI-023: Screen Reader Support**  
**Priority:** MEDIUM  
All UI elements shall provide accessibility labels:
- Note name display: "Detected note: A sharp 4"
- Cent value: "Deviation: minus 12.3 cents"
- Meter needle: "Tuning meter showing flat by 12 cents"
- Buttons: Clear descriptive labels (not just icons)
- Status: Announce tuning status changes ("In tune", "Flat", "Sharp")

**UI-024: Dynamic Type Support (iOS)**  
**Priority:** LOW  
The interface should adapt to user-configured text size preferences where feasible without breaking layout (e.g., button labels, help text, settings screen).

**UI-025: High Contrast Mode Compatibility**  
**Priority:** LOW  
The interface should remain usable when device is in high contrast mode, ensuring:
- Borders remain visible on key elements
- Color-coded zones retain distinguishability through patterns or brightness contrast

**UI-026: Reduced Motion Accommodation**  
**Priority:** LOW  
When device reduced motion setting is enabled:
- Meter needle animation may use instant position updates rather than smooth interpolation
- Transition animations simplified or removed
- Core functionality unaffected

#### 5.1.7 Loading and Error States

**UI-027: Launch Screen**  
**Priority:** MEDIUM  
A brief launch screen shall display during app initialization:
- Application logo or name
- Minimal branding
- Duration: <1 second on typical devices
- Transition smoothly to main interface

**UI-028: Microphone Permission Prompt**  
**Priority:** CRITICAL  
When microphone permission is not granted:
- Display platform-standard permission request dialog
- If denied, show explanation: "Microphone access is required for pitch detection. Please grant permission in Settings."
- Provide "Open Settings" button linking to system app settings

**UI-029: Audio Initialization Error**  
**Priority:** HIGH  
If audio system fails to initialize:
- Display error message: "Unable to access audio. Please check permissions and restart the app."
- Provide "Retry" button to attempt reinitialization
- Provide "Settings" button if permission-related

**UI-030: Background Mode Notification**  
**Priority:** LOW  
When app is resumed from background (future enhancement):
- Optional brief message: "Tap to resume tuning" if tone was playing
- Automatic resumption of pitch detection in Meter Mode (tone generation requires manual restart)

---

### 5.2 Software Interfaces

#### 5.2.1 JUCE Framework Interface

**SI-001: JUCE Version Requirement**  
**Priority:** CRITICAL  
The application shall interface with JUCE framework version 7.0 or later, utilizing the following modules:

- **juce_audio_basics:** Audio buffer manipulation, sample type definitions
- **juce_audio_devices:** Audio I/O device management, AudioDeviceManager
- **juce_audio_processors:** Audio processing base classes (if used for modular design)
- **juce_dsp:** Mathematical functions, DSP utilities for autocorrelation
- **juce_gui_basics:** Component base classes, graphics contexts, touch event handling
- **juce_gui_extra:** Additional GUI utilities if needed
- **juce_core:** String, memory, thread, and file utilities
- **juce_data_structures:** Value tree and data structure utilities
- **juce_events:** Message loop, timer, asynchronous callbacks

**SI-002: Audio Device Manager Interface**  
**Priority:** CRITICAL  
The application shall interface with JUCE's `AudioDeviceManager` class to:
- Initialize audio hardware with preferred configuration
- Enumerate available input/output devices
- Configure sample rate and buffer size
- Register audio callback implementing `AudioIODeviceCallback` interface
- Handle device changes and errors
- Release audio resources when backgrounded

**SI-003: Autocorrelation Implementation**
**Priority:** CRITICAL
The application shall implement autocorrelation-based pitch detection using McLeod Pitch Period Method:
- Compute Normalized Square Difference Function (NSDF) over audio input buffers
- Identify peak locations in NSDF corresponding to pitch period candidates
- Apply parabolic interpolation for sub-sample period accuracy
- Select highest-clarity peak as fundamental period
- Convert period to frequency for pitch detection
- Interface shall support analysis window sizes from 2048 to 8192 samples for flexibility in frequency resolution vs. latency tradeoff

**SI-004: Component Hierarchy Interface**  
**Priority:** CRITICAL  
The application shall use JUCE's GUI component hierarchy:
- Main application window extends `DocumentWindow` or `Component`
- Custom meter display extends `Component` with overridden `paint()` method
- Buttons, labels, sliders use JUCE's built-in component classes
- Touch events handled through `mouseDown()`, `mouseDrag()`, `mouseUp()` callbacks
- Layout management through `resized()` callback responding to size changes

**SI-005: Application Lifecycle Interface**  
**Priority:** CRITICAL  
The application shall implement JUCE's application lifecycle through:
- `JUCEApplication` base class for application entry point
- `initialise()`: Setup audio, load preferences
- `shutdown()`: Release audio, save preferences
- `systemRequestedQuit()`: Handle termination requests
- `suspended()` / `resumed()`: Handle mobile background transitions

#### 5.2.2 iOS Platform Interfaces

**SI-006: iOS Audio Session Interface**  
**Priority:** CRITICAL  
The application shall interface with iOS AVAudioSession for:
- Setting audio session category (e.g., `AVAudioSessionCategoryRecord`, `AVAudioSessionCategoryPlayback`)
- Configuring audio session mode (e.g., `AVAudioSessionModeMeasurement` for low-latency input)
- Requesting preferred sample rate and buffer duration
- Handling audio route changes (headphone connect/disconnect)
- Responding to audio interruptions (phone calls, alarms)
- Requesting permission for microphone access

**SI-007: iOS Permission Interface**  
**Priority:** CRITICAL  
The application shall interface with iOS permission system:
- Query `AVAudioSession.recordPermission` status
- Request microphone permission via `requestRecordPermission()`
- Handle permission status changes
- Provide deep link to Settings app if permission denied

**SI-008: iOS UserDefaults Interface**  
**Priority:** CRITICAL  
The application shall use `UserDefaults` for persistent storage:
- Key-value storage for reference pitch preference
- Synchronize writes to ensure persistence
- Read preferences on launch with default fallback
- Store as integer or string; no complex data structures

**SI-009: iOS Device Orientation Interface**  
**Priority:** CRITICAL  
The application shall interface with iOS orientation system:
- Query `UIDevice.current.orientation` or `UIInterfaceOrientation`
- Register for `UIDeviceOrientationDidChange` notifications
- Respond to orientation changes in layout code
- Support `.portrait`, `.portraitUpsideDown`, `.landscapeLeft`, `.landscapeRight`

#### 5.2.3 Android Platform Interfaces

**SI-010: Android Audio Interface**  
**Priority:** CRITICAL  
The application shall interface with Android audio subsystems:
- **OpenSL ES:** Via JUCE abstraction for Android API <27
- **AAudio:** Via JUCE abstraction for Android API ≥27 (lower latency)
- **AudioManager:** For device routing and volume control
- Configure audio stream with `STREAM_MUSIC` usage
- Set performance mode to `AAUDIO_PERFORMANCE_MODE_LOW_LATENCY` where available

**SI-011: Android Permission Interface**  
**Priority:** CRITICAL  
The application shall interface with Android runtime permissions:
- Check `RECORD_AUDIO` permission status via `ContextCompat.checkSelfPermission()`
- Request permission via `ActivityCompat.requestPermissions()`
- Handle permission result in `onRequestPermissionsResult()` callback
- Provide rationale if user previously denied permission

**SI-012: Android SharedPreferences Interface**  
**Priority:** CRITICAL  
The application shall use `SharedPreferences` for persistent storage:
- Access via `Context.getSharedPreferences()` with app-specific file name
- Use `putInt()` or `putString()` for reference pitch value
- Call `commit()` or `apply()` to persist changes
- Read with `getInt()` or `getString()` providing default value

**SI-013: Android Activity Lifecycle Interface**  
**Priority:** CRITICAL  
The application shall respond to Android activity lifecycle callbacks:
- `onCreate()`: Initialize application and audio systems
- `onResume()`: Restore audio processing
- `onPause()`: Suspend audio processing
- `onStop()`: Release audio resources
- `onDestroy()`: Final cleanup
- Handle configuration changes (orientation) appropriately

**SI-014: Android Screen Orientation Interface**  
**Priority:** CRITICAL  
The application shall handle configuration changes:
- Query current orientation via `Resources.getConfiguration().orientation`
- Respond to `onConfigurationChanged()` callback
- Update layout for `ORIENTATION_PORTRAIT` and `ORIENTATION_LANDSCAPE`
- Optionally lock orientation via `setRequestedOrientation()` in activity

#### 5.2.4 No External API Dependencies

**SI-015: No Network APIs**  
**Priority:** CRITICAL  
The application shall NOT interface with:
- HTTP client libraries or network sockets
- Cloud service APIs (AWS, Firebase, etc.)
- Third-party analytics SDKs (except platform-provided opt-in crash reporting)
- Social media APIs
- Advertisement networks
- Remote configuration services

**SI-016: No Database Systems**  
**Priority:** CRITICAL  
The application shall NOT interface with:
- SQLite or other relational databases
- Realm or other mobile databases
- Core Data (iOS) for persistent storage beyond UserDefaults

Rationale: Minimal data persistence requirements do not justify database complexity.

**SI-017: No External Libraries Beyond JUCE**  
**Priority:** HIGH  
The application shall minimize dependencies beyond JUCE framework:
- No third-party audio processing libraries
- No UI component libraries
- No utility libraries (use C++ standard library or JUCE utilities)
- Exception: Platform SDKs required by JUCE framework itself

---

### 5.3 Hardware Interfaces

#### 5.3.1 Microphone Interface

**HI-001: Microphone Input Configuration**  
**Priority:** CRITICAL  
The application shall interface with device microphone(s) through platform audio APIs:
- **Channel configuration:** Mono input (single channel)
- **Sample format:** 32-bit float or 16-bit signed integer (platform-dependent, JUCE normalizes)
- **Sample rate:** Device native rate, typically 44.1 kHz or 48 kHz
- **Buffer size:** Minimum size supported by hardware, typically 256-512 samples
- **Microphone selection:** Platform-default microphone (bottom microphone on typical smartphones)

**HI-002: Microphone Sensitivity**  
**Priority:** HIGH  
The application shall accommodate microphone sensitivity variations:
- **Expected range:** -40 dBFS (quiet input) to -6 dBFS (loud input)
- **Clipping detection:** Monitor for samples approaching ±1.0 normalized value
- **Automatic gain:** Rely on device automatic gain control or implement software normalization
- **No calibration:** Do not require user calibration of microphone sensitivity

**HI-003: Microphone Frequency Response**  
**Priority:** MEDIUM  
The application shall accommodate typical consumer microphone frequency responses:
- **Optimized range:** 100 Hz - 4000 Hz (typical microphone emphasis)
- **Extended range:** 60 Hz - 16000 Hz (partial coverage)
- **Limitations acknowledged:** Frequencies below 80 Hz and above 5000 Hz may have reduced accuracy due to microphone rolloff
- **No frequency compensation:** Do not implement equalization curves for specific devices

**HI-004: Microphone Directivity**  
**Priority:** LOW  
The application shall function with omnidirectional device microphones:
- **Typical pattern:** Omnidirectional or cardioid-like
- **Positioning:** User should position instrument or voice within 30-100 cm of device
- **Background rejection:** Algorithm should reject distant sounds via level threshold
- **No directional optimization:** Do not require specific device orientation relative to sound source

**HI-005: External Microphone Support**  
**Priority:** LOW  
The application shall support external microphones when connected:
- **Wired headsets:** 3.5mm jack headset microphones (if device has jack)
- **Bluetooth headsets:** Bluetooth microphone input
- **Audio interfaces:** USB or Lightning audio interfaces (if supported by device OS)
- **Automatic switching:** Platform handles routing; application uses active input device
- **No preference setting:** Do not provide microphone selection UI (use system default)

#### 5.3.2 Speaker/Audio Output Interface

**HI-006: Audio Output Configuration**  
**Priority:** CRITICAL  
The application shall interface with device audio output:
- **Channel configuration:** Stereo output (2 channels, identical signal in both)
- **Sample format:** 32-bit float or 16-bit signed integer (platform-dependent)
- **Sample rate:** Match device native rate (44.1 kHz or 48 kHz)
- **Buffer size:** Match input buffer size for consistent latency
- **Output routing:** Platform-default output (speaker, headphones, or Bluetooth)

**HI-007: Speaker Output Level**  
**Priority:** HIGH  
The application shall generate reference tones at appropriate levels:
- **Peak amplitude:** -12 dBFS to -6 dBFS (moderate level)
- **User control:** Respect device system volume setting
- **No volume normalization:** Do not override user's volume preference
- **Prevent clipping:** Ensure synthesized waveform does not exceed ±1.0 normalized range

**HI-008: Speaker Frequency Response**  
**Priority:** MEDIUM  
The application shall accommodate mobile speaker limitations:
- **Optimized range:** 200-600 Hz (reference tone range C4-C5)
- **Speaker rolloff:** Acknowledge bass response typically weak below 200 Hz
- **No compensation:** Do not attempt to equalize speaker response
- **Tone range limitation:** Restrict reference tones to range reproducible by mobile speakers

**HI-009: External Speaker Support**  
**Priority:** MEDIUM  
The application shall support external audio outputs:
- **Wired headphones:** 3.5mm jack or USB-C/Lightning headphones
- **Bluetooth headphones:** A2DP profile for high-quality audio
- **External speakers:** Bluetooth speakers, AirPlay (iOS), Chromecast Audio (Android)
- **Automatic routing:** Platform handles output selection; application uses active output
- **No output selection:** Do not provide audio output device selection UI

#### 5.3.3 Touchscreen Interface

**HI-010: Touch Input Handling**  
**Priority:** CRITICAL  
The application shall interface with capacitive touchscreen:
- **Touch events:** Single-finger touch (tap, press, drag)
- **Multi-touch:** Not required; UI does not use pinch, rotate, or multi-finger gestures
- **Touch precision:** Interface designed for finger-sized targets (44 pt / 48 dp minimum)
- **Touch feedback:** Immediate visual feedback within 100 ms of touch detection
- **Gesture recognition:** Platform handles basic gestures (tap, long-press, swipe)

**HI-011: Screen Resolution Interface**  
**Priority:** CRITICAL  
The application shall adapt to various screen resolutions:
- **iOS range:** 750×1334 (iPhone SE) to 1284×2778 (iPhone 14 Pro Max)
- **Android range:** 720×1280 (HD) to 1440×3200 (QHD+)
- **Density-independent:** Use platform density-independent units (points on iOS, dp on Android)
- **Vector graphics:** Use scalable graphics where possible (SVG, programmatic drawing)
- **Bitmap resources:** Provide multiple resolutions (1×, 2×, 3× on iOS; mdpi, hdpi, xhdpi, xxhdpi, xxxhdpi on Android)

**HI-012: Display Refresh Rate**  
**Priority:** MEDIUM  
The application shall support various display refresh rates:
- **Typical rates:** 60 Hz (standard), 90 Hz, 120 Hz (high refresh)
- **Frame rate:** Target 30 FPS minimum, 60 FPS preferred for smooth animation
- **VSync:** Use platform VSync for tear-free rendering
- **No explicit control:** Do not programmatically set refresh rate; use device default

#### 5.3.4 Device Sensors (Orientation)

**HI-013: Accelerometer/Orientation Sensor Interface**  
**Priority:** HIGH  
The application shall interface with orientation sensors indirectly through platform APIs:
- **Sensor usage:** Platform provides aggregated orientation state
- **Orientation detection:** Portrait, landscape-left, landscape-right, portrait-upside-down
- **Update frequency:** Respond to orientation change events (not raw sensor data)
- **No direct sensor access:** Do not read accelerometer or gyroscope data directly

**HI-014: No Other Sensor Requirements**  
**Priority:** N/A  
The application shall NOT require:
- GPS/location sensors
- Camera
- Proximity sensor
- Ambient light sensor
- Magnetometer
- Barometer
- Biometric sensors (fingerprint, Face ID)

These sensors may be present but are not used by the application.

#### 5.3.5 Storage Interface

**HI-015: Persistent Storage Access**  
**Priority:** CRITICAL  
The application shall interface with device storage:
- **Storage type:** Flash storage (NAND) standard in mobile devices
- **Storage mechanism:** Platform key-value storage (UserDefaults, SharedPreferences)
- **Storage location:** Application sandbox/private storage
- **Storage size:** <1 KB total for preferences
- **No file I/O:** Do not create files in documents or external storage
- **No cache files:** Do not create temporary cache files

**HI-016: Memory (RAM) Interface**  
**Priority:** HIGH  
The application shall interface with device RAM:
- **Minimum RAM:** 2 GB (as per device requirements)
- **Typical usage:** 30-50 MB including audio buffers and UI
- **Maximum usage:** 50 MB to avoid memory pressure on low-end devices
- **Memory warnings:** Respond to platform low-memory warnings by releasing cached data
- **No memory leaks:** Ensure proper resource cleanup to prevent gradual memory growth

---

### 5.4 Communications Interfaces

#### 5.4.1 No Network Communication

**CI-001: Network Interface Prohibition**  
**Priority:** CRITICAL  
The application shall NOT utilize any network communication interfaces:
- No Wi-Fi data transmission
- No cellular data transmission
- No Bluetooth data transmission (Bluetooth audio routing is acceptable)
- No NFC communication
- No peer-to-peer networking (AirDrop, Android Beam, Wi-Fi Direct)

**Rationale:** Offline-only operation is a core requirement ensuring functionality without connectivity and enhancing privacy.

**CI-002: No Internet Protocol Communication**  
**Priority:** CRITICAL  
The application shall NOT implement or use:
- TCP/IP sockets
- UDP sockets
- HTTP/HTTPS requests
- WebSocket connections
- FTP or other file transfer protocols
- SMTP, POP3, or IMAP (email protocols)

**CI-003: No Cloud Service Integration**  
**Priority:** CRITICAL  
The application shall NOT integrate with:
- Cloud storage services (iCloud, Google Drive, Dropbox, OneDrive)
- Cloud messaging services (Firebase Cloud Messaging, Apple Push Notification Service)
- Cloud synchronization services
- Backend-as-a-service platforms (Firebase, AWS Amplify, Parse)

**CI-004: No External API Calls**  
**Priority:** CRITICAL  
The application shall NOT make API calls to:
- RESTful web services
- GraphQL endpoints
- SOAP web services
- Third-party APIs (analytics, advertising, social media)

#### 5.4.2 Inter-Process Communication (Local Only)

**CI-005: Platform Audio Routing**  
**Priority:** HIGH  
The application shall communicate with platform audio subsystems via local inter-process communication:
- **iOS:** Communication with Core Audio daemon via Mach messaging (abstracted by JUCE)
- **Android:** Communication with AudioFlinger via Binder IPC (abstracted by JUCE)
- **Scope:** Audio buffer exchange and control messages only
- **Security:** Platform-enforced sandbox restrictions apply

**CI-006: Platform Services Communication**  
**Priority:** MEDIUM  
The application shall communicate with local platform services:
- **Permission dialogs:** Inter-process communication with permission service
- **Settings app:** Deep linking to system settings (no data exchange)
- **App store:** No direct communication; user manually accesses store for updates

**CI-007: No Custom URL Schemes**  
**Priority:** LOW  
The application shall NOT register custom URL schemes for inter-app communication in Version 1.0. Future versions may support deep linking if needed.

**CI-008: No App Extensions**  
**Priority:** LOW  
The application shall NOT provide app extensions (iOS widgets, Android widgets, share extensions, today extensions) in Version 1.0. Future versions may add widgets showing last detected note.

#### 5.4.3 Data Exchange Formats

**CI-009: No Import/Export Functionality**  
**Priority:** HIGH  
The application shall NOT support data import or export in Version 1.0:
- No file format reading (MIDI, MusicXML, audio files)
- No data export (CSV, JSON, XML)
- No sharing of tuning data to other applications
- Future versions may add tuning history export

**CI-010: No Clipboard Integration**  
**Priority:** LOW  
The application shall NOT copy data to device clipboard in Version 1.0. Future versions may support copying reference pitch or detected pitch information.

#### 5.4.4 Bluetooth Audio Routing

**CI-011: Bluetooth Audio Support**  
**Priority:** MEDIUM  
While Bluetooth data communication is prohibited, Bluetooth audio routing is supported:
- **Bluetooth headphones:** A2DP profile for audio output
- **Bluetooth headsets:** HSP/HFP profile for microphone input and audio output
- **Routing:** Automatic via platform audio system
- **No Bluetooth control:** Application does not control Bluetooth pairing or device selection
- **No data exchange:** Only audio streams routed; no data communication with Bluetooth devices

**Exception Justification:** Bluetooth audio is an extension of hardware audio interfaces, not data communication, and is essential for users preferring wireless audio.

---

## 6. Quality Attributes

This section defines non-functional requirements addressing quality characteristics critical to application success.

### 6.1 Usability

**Usability addresses the ease with which users can learn, operate, and derive value from the application.**

**US-001: Learnability**  
**Priority:** HIGH  
**Requirement:** Users with basic smartphone experience and minimal music theory knowledge shall be able to perform basic tuning operations (detect if instrument is flat/sharp/in-tune) within 2 minutes of first launching the application without consulting help documentation.

**Measurement:**
- Success criterion: 80% of test users (n=20, mixed amateur/professional musicians) achieve successful tuning within 2 minutes in usability testing
- Method: Observe first-time users attempting to tune a guitar string; time to successful tuning recognition

**US-002: Efficiency for Frequent Users**  
**Priority:** HIGH  
**Requirement:** Experienced users shall be able to switch between Meter Mode and Sound Mode, adjust reference pitch, and select reference tones with minimal interaction overhead.

**Measurement:**
- Mode switch: 1 tap maximum
- Reference pitch adjustment by 1-10 Hz: 1-10 taps (increment/decrement)
- Reference tone selection: 1 tap to select note + 1 tap to activate
- Settings access: 2 taps maximum from main screen

**US-003: Error Prevention**  
**Priority:** MEDIUM  
**Requirement:** The interface shall prevent common user errors through design:
- Cannot accidentally switch modes while tuning (requires deliberate tap on mode control)
- Cannot set reference pitch outside valid range (controls disabled at bounds)
- Clear distinction between "select note" and "play tone" actions in Sound Mode

**Measurement:**
- Error rate: <5% of interactions result in unintended actions in usability testing
- No destructive actions requiring confirmation (no data to destroy)

**US-004: Visual Clarity**  
**Priority:** HIGH  
**Requirement:** Critical information (note name, tuning status) shall be legible from typical usage distance of 30-100 cm in varied lighting conditions (indoor ambient light 300-500 lux, stage lighting 100-200 lux, bright outdoor 10,000+ lux).

**Measurement:**
- Contrast ratio: ≥4.5:1 for all text (WCAG AA)
- Note name size: ≥48 pt, occupying 15%+ of screen height
- User study: 90% of users can read tuning status at 1 meter distance

**US-005: Consistency**  
**Priority:** MEDIUM  
**Requirement:** The application shall maintain consistent interaction patterns:
- Mode selection always in same location across orientations
- Settings access always via gear icon in consistent corner
- Touch targets maintain consistent size and spacing
- Visual feedback (highlights, animations) consistent across all interactive elements

**Measurement:**
- Zero inconsistencies identified in interface audit
- User confusion rate: <10% of users seek missing features in wrong location during testing

**US-006: Feedback Responsiveness**  
**Priority:** HIGH  
**Requirement:** The application shall provide immediate feedback for all user interactions:
- Touch feedback: Visual change within 100 ms
- Mode switch: UI update within 200 ms
- Reference pitch change: Calculation and display update within 100 ms
- Tone generation start/stop: Audio response within 10 ms

**Measurement:**
- Measure interaction-to-feedback latency using high-speed video analysis
- Target: 100% of interactions meet specified timing requirements

**US-007: Help Accessibility**  
**Priority:** MEDIUM  
**Requirement:** Help information shall be accessible within 2 taps from any screen, and help content shall address common user questions (What are cents? What is reference pitch? How do I interpret the meter?).

**Measurement:**
- Help access: ≤2 taps verified through UI flow analysis
- Help comprehension: 80% of users answer basic conceptual questions correctly after reading help in user study

**US-008: Graceful Degradation**  
**Priority:** HIGH  
**Requirement:** When errors occur (microphone unavailable, audio initialization failure), the application shall display clear, actionable error messages rather than crashing or freezing.

**Measurement:**
- Error handling coverage: 100% of identified error conditions display user-friendly messages
- Recovery options: All error states provide "Retry" or "Settings" actions
- Crash rate: <0.5% of sessions (See RE-001)

**US-009: Minimal Cognitive Load**  
**Priority:** HIGH  
**Requirement:** The primary tuning workflow shall require minimal cognitive processing:
- Meter Mode: Play note → See flat/center/sharp indication (1-2 second comprehension)
- Sound Mode: Select note → Press play → Hear tone (3-4 second workflow)

**Measurement:**
- Task completion time: 90% of users complete basic tuning tasks in <30 seconds
- Mental effort rating: Average NASA TLX mental demand score <40 (out of 100) in user study

**US-010: Internationalization Readiness**  
**Priority:** LOW  
**Requirement:** The user interface shall be designed to accommodate future localization:
- Text elements use localized string resources (not hard-coded)
- Layout accommodates text expansion (e.g., German text ~30% longer than English)
- Icons and symbols language-neutral where possible

**Measurement:**
- Code review confirms externalized strings
- UI layout tested with 30% longer text strings without breaking

---

### 6.2 Performance

**Performance addresses system responsiveness, throughput, and resource efficiency.**

**PE-001: Pitch Detection Latency**
**Priority:** CRITICAL
**Requirement:** The system shall detect pitch and update the display with latency ≤100 ms from audio input to screen display on 90% of supported devices under normal operating conditions (CPU <60% utilized, device not overheating).

**Measurement:**
- Method: Compare audio input waveform timestamp to display update timestamp using high-speed camera synchronized with audio interface
- Devices tested: Minimum 3 iOS devices (iPhone SE, iPhone 12, iPhone 14), 5 Android devices (low-end to flagship)
- Pass criterion: 90% of test devices achieve ≤100 ms latency
- **Note:** 4096-sample buffer (93ms @ 44.1kHz) required for accurate C1 (32.7 Hz) detection

**PE-002: Tone Generation Latency**  
**Priority:** CRITICAL  
**Requirement:** Reference tone generation shall begin within 10 ms of user pressing play button, with no audible clicking artifacts.

**Measurement:**
- Audio analysis: Measure time from touch event to first tone sample output
- Artifact detection: Inspect waveform for discontinuities causing clicks; spectral analysis for high-frequency artifacts
- Pass criterion: <10 ms latency, no clicks detected

**PE-003: Display Update Frequency**  
**Priority:** HIGH  
**Requirement:** The tuning meter needle and cent value shall update at minimum 20 Hz (50 ms period) to provide smooth visual feedback during continuous pitch input.

**Measurement:**
- Frame rate logging: Measure actual UI update frequency during active pitch detection
- Pass criterion: 95% of updates occur within 50 ms of preceding update

**PE-004: Application Launch Time**  
**Priority:** MEDIUM  
**Requirement:** The application shall launch and display functional interface within 2 seconds on devices meeting minimum specifications (iPhone 6s / Android 8.0 with 2 GB RAM).

**Measurement:**
- Cold launch: From tap on app icon to display of Meter Mode with active pitch detection
- Warm launch: From background to active (≤1 second)
- Pass criterion: 95% of cold launches complete in ≤2 seconds on minimum-spec devices

**PE-005: Mode Switch Responsiveness**  
**Priority:** HIGH  
**Requirement:** Switching between Meter Mode and Sound Mode shall complete within 200 ms, including UI redraw and audio system reconfiguration.

**Measurement:**
- High-speed video: Measure from touch on mode control to display of new mode interface
- Pass criterion: 100% of mode switches in ≤200 ms

**PE-006: CPU Utilization**  
**Priority:** HIGH  
**Requirement:** The application shall consume ≤15% CPU during active pitch detection (Meter Mode) and ≤5% CPU during tone generation (Sound Mode) on devices meeting minimum specifications, allowing device to remain cool and preserve battery life.

**Measurement:**
- Profiling tools: Measure CPU usage over 5-minute active session on minimum-spec devices
- Pass criterion: Average CPU ≤15% (Meter) / ≤5% (Sound); peaks ≤25%

**PE-007: Memory Footprint**  
**Priority:** HIGH  
**Requirement:** The application shall consume ≤50 MB of RAM during normal operation, including audio buffers, UI, and application code.

**Measurement:**
- Memory profiling: Measure peak resident memory size over 30-minute session
- Pass criterion: Peak memory ≤50 MB on all tested devices; no memory leaks (growth <1 MB over 30 minutes)

**PE-008: Battery Consumption**  
**Priority:** MEDIUM  
**Requirement:** During active use (screen on, pitch detection or tone generation), the application shall not cause device temperature increase >3°C above baseline, indicating acceptable power consumption.

**Measurement:**
- Thermal measurement: Monitor device temperature with IR thermometer or device thermal sensors during 10-minute continuous use
- Pass criterion: Temperature increase ≤3°C; device remains comfortable to hold

**PE-009: Audio Buffer Underrun Rate**  
**Priority:** CRITICAL  
**Requirement:** Audio processing shall achieve <0.1% buffer underrun rate (glitches, dropouts, clicks) during normal operation, indicating real-time deadlines consistently met.

**Measurement:**
- Audio logging: Count buffer underruns during 30-minute session
- Pass criterion: <18 underruns per 30 minutes (0.1% of buffers at 100 Hz callback rate)

**PE-010: Orientation Change Performance**  
**Priority:** MEDIUM  
**Requirement:** Device orientation changes shall complete layout recalculation and redraw within 200 ms without interrupting audio processing.

**Measurement:**
- Video capture: Measure from physical device rotation to completed UI redraw
- Audio continuity: Verify no audio dropouts during orientation change
- Pass criterion: 100% of orientation changes in ≤200 ms with uninterrupted audio

**PE-011: Storage I/O Performance**  
**Priority:** LOW  
**Requirement:** Reading and writing user preferences (reference pitch) shall complete within 50 ms to avoid UI blocking during settings access.

**Measurement:**
- Storage profiling: Measure UserDefaults/SharedPreferences read/write latency
- Pass criterion: 100% of storage operations in ≤50 ms

**PE-012: Scalability to Device Spectrum**  
**Priority:** HIGH  
**Requirement:** The application shall maintain acceptable performance (PE-001 through PE-006) across the range of supported devices from minimum specifications to flagship models.

**Measurement:**
- Device matrix testing: Test on 8+ devices spanning release years and price points
- Pass criterion: All devices meet critical performance requirements (PE-001, PE-002, PE-006, PE-009)

---

### 6.3 Security

**Security addresses protection of user data and prevention of unauthorized access or malicious use.**

**SE-001: Data Privacy - No Data Collection**  
**Priority:** CRITICAL  
**Requirement:** The application shall not collect, store, or transmit any personally identifiable information (PII) or user behavior data beyond what is strictly necessary for core functionality (reference pitch preference stored locally).

**Verification:**
- Code audit: Verify no network communication code present
- No analytics SDKs integrated (except platform opt-in crash reporting)
- No user tracking or telemetry

**SE-002: Microphone Data Handling**  
**Priority:** CRITICAL  
**Requirement:** Audio captured from microphone shall be processed in memory only and shall never be written to storage or transmitted over any communication channel.

**Verification:**
- Code audit: Verify no file write operations on audio buffers
- No audio recording API calls present
- No network transmission of audio data

**SE-003: Local Storage Security**  
**Priority:** MEDIUM  
**Requirement:** User preferences (reference pitch) stored locally shall use platform-standard secure storage mechanisms:
- iOS: UserDefaults in application sandbox with default encryption
- Android: SharedPreferences in application private directory with default permissions

**Verification:**
- Storage location verification: Confirm data stored in app-private location
- Permissions verification: Confirm no world-readable or world-writable files created

**SE-004: Microphone Permission Transparency**  
**Priority:** HIGH  
**Requirement:** Microphone permission shall be requested with clear explanation of usage, and application shall function without microphone access by disabling Meter Mode and allowing Sound Mode operation.

**Verification:**
- Permission dialog text clearly states: "Required for pitch detection..."
- Application does not crash or freeze if permission denied
- Sound Mode remains functional without microphone access

**SE-005: No Security-Sensitive Data**  
**Priority:** N/A  
**Requirement:** The application does not handle security-sensitive data requiring encryption:
- No user credentials or passwords
- No payment information
- No health data
- No location data
- No contact information

**Verification:**
- Design review confirms no security-sensitive data in scope

**SE-006: Secure Development Practices**  
**Priority:** MEDIUM  
**Requirement:** Application development shall follow secure coding practices:
- No hard-coded secrets or API keys (none required)
- Input validation on user-provided data (reference pitch range checking)
- No use of deprecated or vulnerable APIs
- No execution of dynamic code or eval-like constructs

**Verification:**
- Code review for common vulnerabilities
- Static analysis tool scan (if available)
- Platform security best practices checklist

**SE-007: App Store Code Signing**  
**Priority:** CRITICAL  
**Requirement:** Application binaries submitted to app stores shall be properly code-signed with valid developer certificates, ensuring authenticity and integrity.

**Verification:**
- iOS: Valid Developer Certificate and provisioning profile
- Android: Valid keystore signing with release key
- Verification of signature before submission

**SE-008: Platform Sandbox Compliance**  
**Priority:** CRITICAL  
**Requirement:** The application shall operate entirely within platform-enforced sandbox restrictions, accessing only permitted resources (microphone with permission, speakers, local storage).

**Verification:**
- iOS: Passes App Store review sandbox requirements
- Android: No requests for dangerous permissions beyond RECORD_AUDIO
- No attempt to break out of sandbox

**SE-009: No Third-Party Code Risk**  
**Priority:** MEDIUM  
**Requirement:** By minimizing external dependencies (only JUCE framework), the application reduces supply chain security risks from compromised third-party libraries.

**Verification:**
- Dependency audit: Confirm only JUCE and platform SDKs used
- JUCE framework from official source with integrity verification

**SE-010: Update Security**  
**Priority:** MEDIUM  
**Requirement:** Application updates shall be distributed exclusively through official app stores (Apple App Store, Google Play Store), leveraging store security verification and malware scanning.

**Verification:**
- No alternative update mechanism or auto-update code in application
- Users must manually update via app store

---

### 6.4 Safety

**Safety addresses prevention of harm to users or equipment arising from application use.**

**SA-001: Hearing Safety - Volume Control**  
**Priority:** CRITICAL  
**Requirement:** Reference tones generated in Sound Mode shall respect device system volume settings and shall not override user volume preferences. Tone amplitude shall be limited to safe levels (-12 dBFS to -6 dBFS) preventing acoustic shock.

**Verification:**
- Audio waveform analysis confirms amplitude limits
- User testing confirms comfortable listening volume
- Device volume controls function normally

**SA-002: No Sudden Loud Sounds**  
**Priority:** HIGH  
**Requirement:** The application shall prevent sudden loud sounds that could startle users or cause hearing damage:
- Tone generation uses fade-in envelope (5-10 ms)
- Tone deactivation uses fade-out envelope (5-10 ms)
- No audio glitches producing transient spikes
- Error conditions do not produce loud alert sounds

**Verification:**
- Waveform analysis for transients
- Spectral analysis for high-frequency glitches
- User testing for startling sounds

**SA-003: Visual Safety - No Seizure-Inducing Content**  
**Priority:** HIGH  
**Requirement:** The user interface shall not contain flashing, strobing, or rapidly alternating visual content that could trigger photosensitive epilepsy:
- Meter needle animation smooth and continuous (no rapid flashing)
- No rapidly flashing indicators
- Color transitions gradual

**Verification:**
- Visual inspection of all animations
- Frame-by-frame analysis for flashing content
- Compliance with WCAG 2.1 guideline 2.3 (Seizures and Physical Reactions)

**SA-004: No Distraction in Critical Environments**  
**Priority:** MEDIUM  
**Requirement:** Application documentation (app store description, help screen) shall advise users not to use the application while driving, operating machinery, or in other safety-critical situations where distraction could cause harm.

**Verification:**
- App store description includes safety warning
- Help screen includes appropriate use guidance

**SA-005: Device Temperature Safety**  
**Priority:** MEDIUM  
**Requirement:** The application's CPU and battery usage shall be sufficiently low (PE-006, PE-008) to prevent device overheating that could cause burns or device damage.

**Verification:**
- Thermal testing confirms ≤3°C temperature increase (PE-008)
- No thermal throttling observed during normal use
- Device remains comfortable to hold

**SA-006: No Misuse of Detected Pitch Data**  
**Priority:** LOW  
**Requirement:** The application shall not suggest or enable use cases where relying on pitch detection could cause harm (e.g., medical applications, safety-critical tuning where failure has severe consequences).

**Verification:**
- App store description clearly states intended use (musical instrument tuning)
- No marketing claims suggesting safety-critical applications

**SA-007: Electrical Safety Compliance**  
**Priority:** LOW  
**Requirement:** The application operates on consumer mobile devices that must already comply with electrical safety standards (UL, CE, FCC). The application itself introduces no electrical safety concerns.

**Verification:**
- No hardware component introduced by application
- Relies on platform device compliance with safety standards

---

### 6.5 Reliability

**Reliability addresses consistent correct operation and availability of the application.**

**RE-001: Crash Rate**  
**Priority:** CRITICAL  
**Requirement:** The application shall maintain crash rate below 0.5% of user sessions (fewer than 1 crash per 200 sessions on average).

**Measurement:**
- Platform crash analytics (Xcode Organizer, Google Play Console)
- Target: <0.5% crash-free sessions metric
- Response: Critical crashes addressed within 2 weeks of discovery

**RE-002: Audio Processing Stability**  
**Priority:** CRITICAL  
**Requirement:** The audio processing pipeline shall operate continuously without failure for extended sessions (30+ minutes) under normal conditions, with <0.1% buffer underrun rate (PE-009).

**Verification:**
- Long-duration testing: 30-minute continuous pitch detection session
- Overnight testing: 8-hour tone generation session
- Pass criterion: Zero crashes, <0.1% audio glitches

**RE-003: Graceful Error Handling**  
**Priority:** HIGH  
**Requirement:** All identified error conditions (microphone unavailable, audio initialization failure, storage failure) shall be handled gracefully with user notification and recovery options rather than crashes.

**Verification:**
- Error injection testing: Simulate error conditions (deny permission, disconnect audio, corrupt storage)
- Pass criterion: Zero crashes, all errors produce user-facing messages with recovery options

**RE-004: Memory Leak Prevention**  
**Priority:** HIGH  
**Requirement:** The application shall not exhibit memory leaks causing gradual memory growth over extended use. Memory usage shall remain stable (±5 MB) over 1-hour session.

**Verification:**
- Memory profiling with Instruments (iOS) / Android Profiler
- Measure memory usage at 0, 15, 30, 45, 60 minutes of continuous use
- Pass criterion: Memory growth <5 MB over 1 hour

**RE-005: Data Persistence Reliability**  
**Priority:** HIGH  
**Requirement:** User preferences (reference pitch setting) shall persist reliably across application restarts, device restarts, and OS updates.

**Verification:**
- Set reference pitch to non-default value (e.g., 442 Hz)
- Restart application: Setting retained
- Restart device: Setting retained
- Simulate OS update (difficult to test; rely on platform storage guarantees)

**RE-006: Platform Compatibility Maintenance**  
**Priority:** HIGH  
**Requirement:** The application shall remain functional across supported OS versions (iOS 13+, Android 8.0+) including minor and patch updates within those major versions.

**Verification:**
- Test on multiple OS versions: iOS 13, 14, 15, 16, 17; Android 8, 9, 10, 11, 12, 13, 14
- Regression testing after OS updates
- Pass criterion: No functionality loss on supported OS versions

**RE-007: Recovery from Background/Foreground Transitions**  
**Priority:** HIGH  
**Requirement:** The application shall reliably resume operation when returning to foreground after backgrounding, with audio system reinitialization successful on 99% of transitions.

**Verification:**
- Repeated background/foreground cycling (50+ cycles)
- Measure success rate of audio reinitialization
- Pass criterion: ≥99% successful resumptions

**RE-008: Orientation Change Stability**  
**Priority:** MEDIUM  
**Requirement:** Device orientation changes shall not cause crashes, data loss, or audio interruptions. UI shall reliably redraw in new orientation.

**Verification:**
- Rapid orientation changes during pitch detection and tone generation
- Pass criterion: Zero crashes, zero audio interruptions, correct UI rendering

**RE-009: Concurrent User Interaction Handling**  
**Priority:** MEDIUM  
**Requirement:** Rapid or overlapping user interactions (e.g., repeatedly tapping mode switch, simultaneously pressing multiple buttons) shall not cause crashes or undefined behavior.

**Verification:**
- "Monkey testing" with rapid random taps
- Pass criterion: Zero crashes, predictable behavior (last valid interaction wins)

**RE-010: Platform Interruption Handling**  
**Priority:** HIGH  
**Requirement:** The application shall handle platform interruptions gracefully:
- Incoming phone call: Pause audio, resume after call ends
- Alarm/notification: Briefly pause or duck audio
- Another app starts audio: Release audio resources, display notification to user

**Verification:**
- Simulate interruptions during pitch detection and tone generation
- Pass criterion: Application remains stable, resumes correctly, no crashes

**RE-011: Availability**  
**Priority:** MEDIUM  
**Requirement:** The application shall be available for use whenever the device is powered on and the application is launched. No external service dependencies means 100% availability independent of network conditions.

**Verification:**
- Functional testing in airplane mode
- Functional testing with Wi-Fi and cellular disabled
- Pass criterion: All features operational without network

---

### 6.6 Portability

**Portability addresses ease of adapting the application to different platforms and environments.**

**PO-001: Cross-Platform Codebase**  
**Priority:** CRITICAL  
**Requirement:** The application shall maximize code sharing between iOS and Android platforms, targeting ≥90% shared code through JUCE framework abstraction.

**Measurement:**
- Lines of code analysis: Measure shared C++/JUCE code vs. platform-specific Objective-C++/Java/Kotlin code
- Target: ≥90% shared, ≤10% platform-specific
- Platform-specific code limited to essential integrations (permissions, lifecycle)

**PO-002: Platform Adaptation**  
**Priority:** HIGH  
**Requirement:** While maximizing shared code, the application shall adapt to platform-specific conventions where appropriate:
- Navigation patterns (iOS swipe-back vs. Android hardware back)
- Visual design (iOS rounded corners vs. Android Material Design)
- Permission request flows (platform-standard dialogs)
- Audio API differences (CoreAudio vs. OpenSL ES / AAudio)

**Verification:**
- Platform-specific testing confirms appropriate conventions followed
- User surveys confirm application "feels native" on each platform

**PO-003: Build System Portability**
**Priority:** HIGH
**Requirement:** The application shall use dual build system configuration:
- CMake for local development, desktop testing, and CI/CD automation
- Projucer for mobile platform project generation (iOS Xcode, Android Studio)

Both build systems shall target the same shared codebase with platform-specific conditionals where necessary.

**Verification:**
- CMake generates desktop executable with unit test runner
- Projucer generates iOS Xcode project: Successful iOS build
- Projucer generates Android Studio project: Successful Android build
- CMake and Projucer builds compile identical shared codebase
- Minimal manual configuration required post-generation

**Measurement:**
- Desktop test executable runs on macOS, Windows, Linux
- Mobile builds link against same shared library code
- ≥95% of core algorithm code compiles through both build systems

**PO-004: Dependency Minimization**  
**Priority:** HIGH  
**Requirement:** The application shall minimize dependencies on platform-specific libraries and APIs by using JUCE cross-platform abstractions wherever feasible, simplifying porting and maintenance.

**Verification:**
- Dependency audit lists only JUCE and essential platform frameworks
- No third-party platform-specific libraries

**PO-005: Screen Size Portability**  
**Priority:** HIGH  
**Requirement:** The application's responsive layout shall function correctly across the range of screen sizes and aspect ratios present in the mobile device ecosystem:
- Small phones: 4.7" diagonal, 16:9 aspect ratio
- Standard phones: 5.5-6.1" diagonal, 18:9 to 19.5:9 aspect ratios
- Large phones: 6.5-6.8" diagonal, 19.5:9 to 20:9 aspect ratios

**Verification:**
- Test on minimum 8 devices with varied screen sizes
- Inspect screenshots for layout correctness (no cropping, overlap, illegible text)

**PO-006: OS Version Portability**  
**Priority:** HIGH  
**Requirement:** The application shall support a range of OS versions providing access to broad user base while avoiding excessive legacy support burden:
- iOS: 13.0 through latest (currently iOS 17.x)
- Android: API 26 (Android 8.0) through latest (currently API 34, Android 14)

**Verification:**
- Test on oldest and newest supported OS versions
- Verify no use of APIs unavailable on minimum OS version
- Conditional compilation or runtime checks for newer APIs

**PO-007: Hardware Portability**  
**Priority:** HIGH  
**Requirement:** The application shall function correctly across diverse hardware from minimum specifications (2 GB RAM, 1.4 GHz quad-core) to high-end flagships, with performance scaling gracefully.

**Verification:**
- Test on low-end device (e.g., budget Android phone with 2 GB RAM)
- Test on high-end device (e.g., latest iPhone Pro)
- Verify acceptable performance on both (critical requirements met on low-end, enhanced experience on high-end)

**PO-008: Future Platform Extensibility**  
**Priority:** LOW  
**Requirement:** The application architecture shall facilitate potential future porting to additional platforms (e.g., desktop macOS/Windows, tablets) through JUCE's cross-platform support, though such ports are out of scope for Version 1.0.

**Verification:**
- Architecture review confirms separation of concerns (audio logic, UI, platform integration)
- No hard-coded assumptions specific to mobile form factor where avoidable

**PO-009: Localization Readiness**  
**Priority:** LOW  
**Requirement:** While Version 1.0 supports English only, the codebase shall be structured to facilitate future localization by externalizing strings and supporting variable text lengths in layouts (see US-010).

**Verification:**
- Code audit confirms strings externalized to resource files
- UI layouts tested with 30% text expansion

**PO-010: Compiler Portability**
**Priority:** MEDIUM
**Requirement:** The C++ codebase shall be compilable with platform-standard toolchains without requiring specific compiler versions or extensions:
- iOS: Apple Clang (provided with Xcode)
- Android: Clang (provided with NDK)
- C++17 standard compliance without compiler-specific extensions

**Verification:**
- Successful compilation on macOS with Xcode (various versions)
- Successful compilation with Android NDK on macOS, Windows, Linux
- No compiler warnings at high warning levels (-Wall -Wextra)

**PO-011: Shared Library Architecture**
**Priority:** CRITICAL
**Requirement:** Platform-independent application logic shall be organized into a shared library achieving ≥95% core code isolation from platform-specific implementations.

**Scope:**
- Pitch detection algorithms (PitchDetector, autocorrelation, NSDF)
- Tone generation algorithms (ToneGenerator, sine synthesis)
- Frequency calculations (FrequencyCalculator, equal temperament)
- Configuration management (reference pitch calculations)
- Business logic and state management

**Verification:**
- Static analysis: Lines of code in shared library vs. platform wrappers
- Target: ≥95% of core algorithms in shared library
- Shared library compiles without platform-specific headers
- Unit tests link only against shared library

**Measurement:**
```
Shared Library LOC / (Shared Library LOC + Platform Wrapper LOC) ≥ 0.95
```

**PO-012: Platform Abstraction Interfaces**
**Priority:** HIGH
**Requirement:** The application shall define clean abstraction interfaces for platform-dependent services, enabling desktop test implementations alongside production mobile implementations.

**Required Abstractions:**
1. **Audio I/O Interface:**
   - `getAudioInput()`: Provides microphone samples or test signal injection
   - `writeAudioOutput()`: Routes to speakers or test verification buffer

2. **Storage/Preferences Interface:**
   - `readPreference(key)`: Retrieves stored value or in-memory test value
   - `writePreference(key, value)`: Persists to UserDefaults/SharedPreferences or test mock

3. **Permission Interface:**
   - `requestMicrophonePermission()`: Platform-specific flow or auto-grant in tests
   - `getMicrophonePermissionStatus()`: Returns granted/denied or always-granted in tests

**Verification:**
- Interface definition files contain no platform-specific types
- Desktop test implementations compile and link successfully
- Mobile implementations compile and link successfully
- Shared library code depends only on abstract interfaces, not concrete implementations

**Implementation Pattern:**
```cpp
// Abstract interface (in shared library)
class IAudioInput {
public:
    virtual ~IAudioInput() = default;
    virtual void getAudioSamples(float* buffer, int numSamples) = 0;
};

// Production implementation (mobile platforms)
class JUCEAudioInput : public IAudioInput { /* JUCE AudioDeviceManager */ };

// Test implementation (desktop)
class MockAudioInput : public IAudioInput { /* Inject test signals */ };
```

**PO-013: Desktop Test Runner**
**Priority:** HIGH
**Requirement:** The project shall include a command-line desktop test runner executable enabling automated unit testing of core algorithms without mobile device deployment.

**Scope:**
- **Minimal, not comprehensive:** Unit tests only, not full UI/integration testing
- Tests pitch detection algorithm accuracy
- Tests tone generation algorithm accuracy
- Tests frequency calculation correctness
- Tests configuration management logic
- Runs on developer workstations (macOS, Linux, Windows)

**Out of Scope:**
- Full application UI testing (remains mobile-only)
- Integration testing with real audio hardware (remains mobile-focused)
- Performance/latency testing (mobile devices only)

**Verification:**
- Desktop test executable compiles via CMake
- Test runner executes without requiring mobile device
- Test results output in standard format (TAP, JUnit XML)
- Exit code indicates pass/fail for CI/CD integration

**Metrics:**
- ≥80% code coverage of shared library algorithms
- Test execution completes in <60 seconds on standard development machine

---

### 6.7 Maintainability

**Maintainability addresses ease of understanding, modifying, testing, and extending the codebase.**

**MA-001: Modularity and Separation of Concerns**
**Priority:** HIGH
**Requirement:** The codebase shall be organized into distinct modules with clear responsibilities and minimal coupling:
- **Shared Algorithm Library:** Platform-independent logic (≥95% of core code)
- **Platform Abstraction Layer:** Interface definitions for platform services
- **Platform Implementations:** iOS, Android, Desktop (test) implementations of abstractions
- **UI Layer:** Platform-specific user interface code

**Verification:**
- Dependency analysis confirms shared library has no dependencies on platform implementations
- Module boundaries enforced through build system configuration
- No circular dependencies between modules

**Measurement:**
- Coupling metrics: Shared library imports ≤3 platform-agnostic headers
- Cohesion metrics: Each module has single clear responsibility

**MA-002: Testability**
**Priority:** HIGH
**Requirement:** The codebase shall be designed for automated testing through:
- Dependency injection of platform services
- Pure functions for algorithmic computations where feasible
- Mockable interfaces for external dependencies
- Desktop test harness for rapid iteration

**Verification:**
- ≥80% of shared library code covered by automated unit tests
- Core algorithms testable without platform-specific dependencies
- Test suite executes in CI/CD pipeline

**Measurement:**
- Code coverage percentage (target ≥80% for shared library)
- Number of unit tests (target ≥50 for core algorithms)
- Test execution time (target <60 seconds)

**MA-003: Code Organization and Documentation**
**Priority:** MEDIUM
**Requirement:** Source code shall follow consistent organization and documentation standards:
- Header files declare interfaces with Doxygen-compatible comments
- Implementation files separated from interfaces
- Clear directory structure: `src/shared/`, `src/platform/ios/`, `src/platform/android/`, `src/platform/desktop/`
- README files in each module directory

**Verification:**
- Directory structure audit
- Documentation completeness check (all public APIs documented)
- Consistent naming conventions verified through linting

**MA-004: Build System Maintainability**
**Priority:** MEDIUM
**Requirement:** Build configurations shall be maintainable and reproducible:
- CMakeLists.txt for desktop/CI builds with clear dependency management
- Projucer project for mobile builds with documented setup steps
- Build documentation includes setup instructions for new developers
- Dependency versions pinned and documented

**Verification:**
- New developer can build project following documentation in <30 minutes
- Builds reproducible across development machines
- No "works on my machine" issues

---

## 7. Internationalization and Localization Requirements

**Version 1.0 of the Chromatic Tuner application targets English-language users exclusively. This section defines internationalization and localization requirements for the initial release and establishes the foundation for future multi-language support.**

### 7.1 Version 1.0 Language Support

**IL-001: English-Only Release**  
**Priority:** CRITICAL  
**Requirement:** Version 1.0 shall provide user interface text, help documentation, and app store metadata exclusively in English (United States).

**Justification:**
- Focused scope for timely release
- Volunteer development resources limited
- Music terminology (note names) largely universal using English letters

**IL-002: Note Name Internationalization**  
**Priority:** N/A  
**Requirement:** Note names (C, D, E, F, G, A, B, C#, D#, F#, G#, A#) shall use English letter notation consistently, as this is the internationally recognized standard for chromatic note naming in music education and performance.

**Exception:** Future localized versions may optionally include local note naming conventions where they differ significantly (e.g., German H for B, Latin solfège Do-Re-Mi), but this is not required.

**IL-003: Numeric Format**  
**Priority:** HIGH  
**Requirement:** Numeric displays shall use conventions appropriate for international audiences:
- **Decimal separator:** Period "." (e.g., "12.3 cents", not "12,3")
- **Frequency units:** "Hz" (Hertz) is internationally recognized
- **No thousands separators:** Frequency values under 1000 Hz require no separator

**Rationale:** Music and audio engineering contexts globally use period as decimal separator.

### 7.2 Internationalization Architecture (Future-Proofing)

**IL-004: String Externalization**  
**Priority:** MEDIUM  
**Requirement:** All user-facing text strings shall be externalized to resource files rather than hard-coded in source code, facilitating future translation without code modifications.

**Implementation:**
- iOS: Use NSLocalizedString and Localizable.strings files
- Android: Use strings.xml resource files
- JUCE: Use JUCE's TRANS() macro or equivalent localization mechanism

**Verification:**
- Code audit confirms no hard-coded English strings in UI code
- Grep for English words in C++ source files flags violations

**IL-005: Unicode Support**  
**Priority:** HIGH  
**Requirement:** The application shall handle Unicode text correctly in all text fields, including UTF-8 encoding for strings and proper rendering of extended character sets.

**Rationale:** Future localizations may include non-ASCII characters (accented characters, Cyrillic, CJK).

**Verification:**
- Test display of strings containing accented characters (é, ñ, ü)
- Verify no text corruption or rendering issues

**IL-006: Layout Flexibility**  
**Priority:** MEDIUM  
**Requirement:** User interface layouts shall accommodate text length variations up to +30% from English baseline, ensuring future localizations (e.g., German, Spanish) do not cause text truncation or layout breaking.

**Implementation:**
- Use flexible layouts (auto-layout on iOS, constraint layouts on Android)
- Avoid fixed-width text containers where possible
- Test with artificially lengthened strings

**Verification:**
- UI tested with strings extended by 30% (pseudo-localization)
- No text clipping or button overflow

**IL-007: Right-to-Left (RTL) Language Consideration**  
**Priority:** LOW  
**Requirement:** While RTL languages (Arabic, Hebrew) are not planned for near-term support, the application architecture shall not preclude future RTL support. No hard-coded left-to-right layout assumptions in core design.

**Implementation:**
- Use platform layout abstractions respecting text directionality
- Avoid absolute positioning where relative positioning suffices

**IL-008: Date and Time Formatting**  
**Priority:** N/A  
**Requirement:** Version 1.0 does not display dates or times. If future versions add time-stamped data (e.g., tuning history logs), date/time formatting shall use platform localization APIs to respect user's locale settings.

**IL-009: Currency and Units**  
**Priority:** N/A  
**Requirement:** The application does not display currency (free application) or measurement units beyond musical units (Hz, cents), which are internationally standardized and do not require localization.

### 7.3 Future Localization Scope

**IL-010: Priority Languages for Future Releases**  
**Priority:** LOW  
**Requirement:** If localization is pursued in future releases, priority languages should be selected based on:
1. App store download statistics by region
2. Size of musician population
3. Languages with professional music education systems
4. Volunteer translator availability

**Suggested priorities (subject to data-driven revision):**
- **Tier 1:** Spanish, German, French, Japanese (large musician populations)
- **Tier 2:** Italian, Portuguese, Mandarin Chinese, Korean, Russian
- **Tier 3:** Additional European and Asian languages

**IL-011: Localized Help Content**  
**Priority:** LOW  
**Requirement:** Future localizations shall include translated help documentation explaining:
- Musical terminology (note names, cents, chromatic scale)
- Reference pitch calibration
- Usage instructions

**Challenge:** Musical terminology education varies by region; help content may require cultural adaptation beyond direct translation.

**IL-012: App Store Metadata Localization**  
**Priority:** LOW  
**Requirement:** Future localizations shall include translated app store metadata:
- Application name (if translated)
- Description
- Keywords
- Screenshot captions

**IL-013: No Content Localization Required**  
**Priority:** N/A  
**Requirement:** The application contains no culture-specific content requiring localization:
- No images of people, flags, or cultural symbols
- No region-specific examples or references
- Musical notation and terminology are international

---

## 8. Other Requirements

This section addresses additional requirements not covered in previous sections.

### 8.1 Legal and Licensing Requirements

**OR-001: Software Licensing**  
**Priority:** CRITICAL  
**Requirement:** The application shall comply with all software licenses:
- **JUCE Framework:** Use under JUCE Personal License (GPLv3 for open-source distribution) or JUCE Pro License if commercial features needed. Version 1.0 targets free distribution under Personal License.
- **Platform SDKs:** Comply with Apple and Google developer terms of service
- **Open-source dependencies:** If any open-source code is incorporated beyond JUCE, comply with respective licenses (MIT, Apache, BSD, etc.)

**Verification:**
- License audit of all dependencies
- Legal review of license compatibility
- Include LICENSE file in source repository

**OR-002: Intellectual Property**  
**Priority:** HIGH  
**Requirement:** The application shall not infringe on intellectual property rights:
- No use of copyrighted audio samples or recordings
- No use of trademarked names or logos without permission
- Synthesized tones are mathematical waveforms not subject to copyright
- Application name "Chromatic Tuner" is descriptive, not trademarked

**Verification:**
- Trademark search for application name
- Review of all assets (icons, images) for licensing compliance

**OR-003: Privacy Policy**  
**Priority:** HIGH  
**Requirement:** The application shall provide a privacy policy document addressing:
- Data collection practices (minimal: reference pitch stored locally)
- Microphone usage explanation
- No third-party data sharing
- User rights and data deletion
- Compliance with GDPR, CCPA where applicable

**Verification:**
- Privacy policy drafted and reviewed
- Link included in app store listings and application settings
- Policy hosted on publicly accessible website or included in application

**OR-004: Terms of Service**  
**Priority:** MEDIUM  
**Requirement:** The application may provide terms of service addressing:
- Limitation of liability for tuning accuracy
- Intended use (musical instruments, not safety-critical applications)
- No warranty of fitness for particular purpose
- User responsibilities

**Verification:**
- Terms of service drafted (optional for free utility application)
- If provided, link accessible from settings or about screen

**OR-005: App Store Compliance**  
**Priority:** CRITICAL  
**Requirement:** The application shall comply with app store policies:
- **Apple App Store:** Review Guidelines compliance (no private APIs, appropriate content rating, accurate metadata)
- **Google Play Store:** Developer Policy compliance (no malicious behavior, content rating, accurate metadata)
- **Content rating:** Application suitable for all ages (4+ on iOS, Everyone on Android)

**Verification:**
- Pre-submission review against app store guidelines
- Successful submission and approval

**OR-006: Export Compliance**  
**Priority:** LOW  
**Requirement:** The application shall comply with export regulations:
- No encryption beyond standard platform HTTPS (not used in this application)
- If cryptography used, comply with export control regulations (EAR, ITAR)

**Verification:**
- Application uses no encryption beyond platform-provided data protection (not classified as encryption for export purposes)

### 8.2 Regulatory Requirements

**OR-007: Accessibility Compliance**  
**Priority:** MEDIUM  
**Requirement:** The application should make reasonable efforts toward accessibility compliance:
- Platform screen reader compatibility (VoiceOver, TalkBack)
- Minimum contrast ratios (WCAG AA)
- Touch target sizes meet platform guidelines
- Acknowledge limitations: Visual tuning meter difficult to fully accessibilify for blind users

**Verification:**
- Accessibility audit with screen reader testing
- Contrast ratio verification
- Touch target size measurement

**OR-008: Content Rating**  
**Priority:** CRITICAL  
**Requirement:** The application shall be assigned appropriate content ratings:
- **PEGI:** 3+ (suitable for all age groups)
- **ESRB:** E (Everyone)
- **App Store:** 4+
- **Google Play:** Everyone

**Justification:** No objectionable content; simple utility for musical tuning.

**OR-009: No Gambling or Inappropriate Content**  
**Priority:** N/A  
**Requirement:** The application contains no gambling mechanics, inappropriate content, violence, profanity, or mature themes. This requirement is met by design (utility application).

### 8.3 Installation and Deployment Requirements

**OR-010: Installation Size**  
**Priority:** HIGH  
**Requirement:** The application installation package shall not exceed 25 MB to minimize download barriers, especially for users on cellular connections or with limited device storage.

**Measurement:**
- iOS: .ipa file size ≤25 MB
- Android: .apk file size ≤25 MB
- App thinning (iOS) and split APKs (Android) may reduce actual download size further

**OR-011: Minimum Storage Requirement**  
**Priority:** MEDIUM  
**Requirement:** The application shall require ≤25 MB of device storage for installation, with negligible additional storage for user preferences (<1 KB).

**OR-012: No External Dependencies**  
**Priority:** CRITICAL  
**Requirement:** The application shall not require downloading additional data files, libraries, or resources after installation. All functionality available immediately post-install.

**OR-013: Update Mechanism**  
**Priority:** HIGH  
**Requirement:** Application updates shall be distributed exclusively via app stores:
- Users receive update notifications from platform app store
- No in-app update prompts (rely on platform notifications)
- No automatic background updates managed by application

**OR-014: Backwards Compatibility**  
**Priority:** MEDIUM  
**Requirement:** Application updates shall maintain backward compatibility with stored preferences:
- Reference pitch setting preserved across updates
- Graceful handling of schema version changes (DR-004)
- No data loss during update process

**Verification:**
- Test upgrade from Version 1.0 to Version 1.1 (when available)
- Verify preferences retained and migrated correctly

**OR-015: Uninstallation**  
**Priority:** LOW  
**Requirement:** When application is uninstalled, all application data shall be removed from device according to platform behavior:
- iOS: Application sandbox deleted automatically
- Android: Application data deleted automatically (unless user explicitly backs up)
- No orphaned data or configuration files

### 8.4 Documentation Requirements

**OR-016: User Documentation**  
**Priority:** MEDIUM  
**Requirement:** The application shall provide in-app help documentation addressing:
- Basic usage instructions (Meter Mode, Sound Mode)
- Explanation of musical concepts (notes, cents, reference pitch)
- Troubleshooting tips (no signal, microphone permission)
- Optimal usage conditions

**Format:** Brief text screens accessible from help button, maximum 500 words per topic.

**OR-017: Developer Documentation**  
**Priority:** MEDIUM  
**Requirement:** The project shall maintain developer documentation including:
- README file with build instructions
- Architecture overview documenting major components
- Pitch detection algorithm documentation
- JUCE framework integration notes
- Platform-specific integration details

**Audience:** Future contributors and maintainers.

**OR-018: App Store Listings**  
**Priority:** CRITICAL  
**Requirement:** Application listings on app stores shall include:
- Clear description of functionality
- Screenshots showing Meter Mode and Sound Mode
- List of features (offline operation, chromatic detection, reference tones, calibration)
- System requirements (iOS 13+, Android 8.0+)
- Privacy policy link
- Support contact information

**Verification:**
- Marketing review of app store metadata
- Screenshots captured on representative devices

**OR-019: Version History**  
**Priority:** LOW  
**Requirement:** The project shall maintain a changelog documenting:
- Version number and release date
- New features added
- Bug fixes
- Known issues

**Format:** CHANGELOG.md file in source repository.

### 8.5 Support and Maintenance Requirements

**OR-020: User Support**  
**Priority:** MEDIUM  
**Requirement:** The application shall provide user support through:
- Support email address listed in app store and about screen
- Bug reports and feature requests accepted via email
- Response to critical bugs within 1 week
- No real-time support (phone, chat) due to volunteer nature

**OR-021: Issue Tracking**
**Priority:** MEDIUM
**Requirement:** The project shall maintain issue tracking for:
- Bug reports from users
- Feature requests
- Known issues and workarounds
- Development tasks

**Tool:** GitHub Issues, Jira, or similar platform.

**OR-021A: Continuous Integration Requirements**
**Priority:** HIGH
**Requirement:** The project shall maintain automated continuous integration (CI) pipeline:
- **Desktop Unit Tests:** Execute on every commit to main/feature branches
- **Mobile Builds:** Compile iOS and Android builds to verify compilation
- **Test Gating:** Mobile builds only proceed if desktop unit tests pass
- **Failure Notification:** Team notified within 15 minutes of test failures

**CI Pipeline Stages:**
1. Stage 1: Desktop unit tests (via CMake build and test runner)
2. Stage 2: iOS compilation verification (if Stage 1 passes)
3. Stage 3: Android compilation verification (if Stage 1 passes)

**Verification:**
- CI configuration file present in repository (e.g., `.github/workflows/ci.yml`)
- Commit hooks prevent pushes without passing local tests (optional)
- Build badge displayed in repository README

**Justification:**
- Prevents regression in core algorithms
- Catches platform-specific build issues early
- Desktop tests provide fast feedback (< 5 minutes vs. mobile builds ~20+ minutes)

**OR-022: Critical Bug Response**  
**Priority:** HIGH  
**Requirement:** Critical bugs (crashes, data loss, major functionality breakage) shall be addressed within 2 weeks of discovery:
- Fix developed and tested
- Update submitted to app stores
- Users notified via app store update notes

**OR-023: Routine Updates**  
**Priority:** LOW  
**Requirement:** Non-critical bug fixes and minor features may be batched into quarterly updates to minimize update fatigue.

### 8.6 Future Enhancement Considerations

**OR-024: Planned Future Features**  
**Priority:** LOW  
**Requirement:** The following features are explicitly out of scope for Version 1.0 but may be considered for future releases:
- Alternative tuning systems (just intonation, Pythagorean)
- Instrument-specific presets (guitar, violin, orchestra tunings)
- Tuning history and session logging
- Dark mode / alternative themes
- Multi-language localization
- Transposition support
- Advanced visualizations (spectrum display, waveform)
- Tablet-optimized layouts

**OR-025: Architecture for Extensibility**  
**Priority:** LOW  
**Requirement:** The application architecture should avoid design decisions that would preclude future enhancements where feasible, but extensibility shall not compromise simplicity or performance of Version 1.0.

---

## Appendix A: Glossary

**Analog-style meter:** A visual display mimicking mechanical tuning meters with a needle or pointer moving along an arc to indicate pitch deviation, as opposed to purely numeric or bar-graph displays.

**App store:** Digital distribution platform for mobile applications (Apple App Store for iOS, Google Play Store for Android).

**A4 (A440):** The musical note A above middle C, conventionally tuned to 440 Hz as international concert pitch standard (ISO 16:1975). This frequency serves as the reference for calculating all other note frequencies in equal temperament.

**Buffer underrun:** An error condition in real-time audio processing where the audio processing thread fails to produce output samples or consume input samples within the required time deadline, resulting in audible glitches (clicks, dropouts, silence).

**Cent:** A logarithmic unit of musical interval measurement. One cent is 1/100 of an equal-tempered semitone. The formula for cents is: cents = 1200 × log₂(f₁/f₂), where f₁ and f₂ are two frequencies.

**Chromatic:** Including all twelve pitches of the equal-tempered scale (C, C#, D, D#, E, F, F#, G, G#, A, A#, B) within an octave, as opposed to diatonic (seven-note) scales.

**Clipping:** Distortion occurring when an audio signal exceeds the maximum representable amplitude (±1.0 in normalized representation), causing the waveform to be "clipped" flat at the peaks.

**Cross-platform:** Software designed to function on multiple operating system platforms (iOS and Android in this case) from a largely shared codebase, minimizing platform-specific code.

**dBFS (Decibels Full Scale):** A unit of measurement for audio levels in digital systems, where 0 dBFS represents the maximum possible amplitude before clipping, and negative values represent quieter signals (e.g., -12 dBFS is quieter than -6 dBFS).

**Equal temperament (12-tone equal temperament):** A musical tuning system dividing the octave into twelve equal intervals (semitones), where each semitone represents a frequency ratio of 2^(1/12) ≈ 1.05946. This is the standard tuning system for most modern Western music.

**Autocorrelation:** A signal processing technique that measures the similarity of a signal with a time-shifted version of itself, used in pitch detection to identify periodic patterns corresponding to fundamental frequency.

**Foreground / Background:** Application states on mobile platforms. Foreground: Application visible on screen, receiving user input and system resources. Background: Application not visible, with limited resources and restricted functionality.

**Frequency:** The rate at which a sound wave oscillates, measured in Hertz (Hz). In music, frequency corresponds to perceived pitch: higher frequency = higher pitch.

**Fundamental frequency:** The lowest frequency component of a periodic waveform (such as a musical note). The fundamental frequency determines the perceived pitch, even though higher harmonics (overtones) are also present.

**McLeod Pitch Period Method (McLeod PPM):** A pitch detection algorithm using the Normalized Square Difference Function (NSDF) to identify pitch periods through autocorrelation analysis, providing robust fundamental frequency detection in the presence of harmonics and noise.

**Harmonic / Overtone:** Frequency components of a musical sound that are integer multiples of the fundamental frequency. For example, a note with fundamental 100 Hz contains harmonics at 200 Hz (2nd harmonic), 300 Hz (3rd harmonic), etc.

**Hz (Hertz):** Unit of frequency representing cycles per second. In audio, 440 Hz means the sound wave oscillates 440 times per second.

**JUCE:** A cross-platform C++ framework for developing audio applications, providing abstractions for audio I/O, DSP, GUI, and platform integration. Originally an acronym for "Jules' Utility Class Extensions."

**Just intonation:** A tuning system based on pure integer frequency ratios (e.g., 3:2 for perfect fifth, 5:4 for major third), producing acoustically pure intervals at the cost of key-change complications. Contrasts with equal temperament.

**Latency:** The time delay between an event (e.g., playing a note) and the system's response (e.g., displaying the detected pitch). Low latency (<100 ms) is critical for interactive tuning applications.

**Meter Mode:** The application's operating mode where it continuously monitors microphone input, detects pitch, and displays tuning status with an analog-style meter.

**MIDI note number:** A numerical representation of musical pitches where middle C (C4) = 60, and each semitone increases the number by 1 (C#4 = 61, D4 = 62, etc.). A4 (440 Hz) = 69.

**Octave:** A musical interval where the higher pitch has exactly double the frequency of the lower pitch. Notes separated by one octave have the same name (e.g., A3 at 220 Hz and A4 at 440 Hz).

**NSDF (Normalized Square Difference Function):** A mathematical function used in the McLeod Pitch Period Method to compute autocorrelation with normalization, producing clear peaks at lag values corresponding to the fundamental period of a periodic signal.

**Offline operation:** Application functionality that does not require network connectivity, functioning entirely using local device resources.

**Permission:** Authorization granted by the user allowing an application to access protected resources (microphone, camera, location, etc.). Mobile platforms require explicit user permission for microphone access.

**Pitch:** The perceptual quality of a sound corresponding to its frequency. Higher pitch = higher frequency. In music, pitch is organized into discrete notes (A, B, C, etc.).

**Pitch detection:** The process of analyzing an audio signal to determine its fundamental frequency and identifying the corresponding musical note.

**Pure interval:** A musical interval based on simple integer frequency ratios (e.g., 5:4 for pure major third) rather than equal-tempered approximations. Pure intervals are acoustically consonant but differ slightly from equal-tempered intervals.

**Reference pitch / Reference tone:** A known frequency used as a standard for tuning. In this application, A4 (default 440 Hz) serves as the reference pitch, and the application can generate reference tones for aural tuning.

**Real-time processing:** Computation that must complete within strict time deadlines (audio callback deadlines) to avoid glitches. Real-time audio processing typically occurs in a high-priority thread separate from UI.

**Sample rate:** The number of audio samples captured or generated per second, measured in Hz (typically 44,100 Hz or 48,000 Hz for high-quality audio). Higher sample rates enable representation of higher frequencies.

**Scientific pitch notation:** A system for naming musical pitches using letter names (C, D, E, F, G, A, B) with optional sharps (#) and octave numbers (0-8), where C4 is middle C and A4 is the tuning reference (typically 440 Hz).

**Semitone:** The interval between adjacent notes in the 12-tone equal-tempered scale (e.g., C to C#). One semitone equals 100 cents.

**Sharp / Flat:** Musical notation symbols indicating pitch modification. Sharp (#) raises pitch by one semitone; flat (♭) lowers pitch by one semitone. In tuning, "sharp" means pitch is too high; "flat" means pitch is too low.

**Sine wave:** A smooth, periodic waveform described by the sine function, containing a single frequency with no harmonics. The application generates pure sine waves for reference tones.

**Sound Mode:** The application's operating mode where users select a note and generate a continuous reference tone for aural tuning.

**Touch target:** An interactive user interface element sized for finger-based touch input (minimum 44×44 points on iOS, 48×48 dp on Android).

**Tuner (chromatic tuner):** A device or application that detects the pitch of a musical sound and indicates whether it matches the target frequency (in tune), is too low (flat), or too high (sharp). A chromatic tuner detects all twelve notes rather than being limited to specific instruments.

**UserDefaults (iOS) / SharedPreferences (Android):** Platform-provided mechanisms for storing small amounts of persistent key-value data (preferences) that survive application restarts.

---

## Appendix B: Analysis Models

This appendix provides visual models and diagrams illustrating system architecture, data flow, and behavioral specifications.

### B.1 System Context Diagram

The system context diagram illustrates the Chromatic Tuner application's position within its environment and its interactions with external entities.

```
                          ┌─────────────────────┐
                          │                     │
                          │      Musician       │
                          │   (Primary Actor)   │
                          │                     │
                          └──────────┬──────────┘
                                     │
                    Touch Input      │      Visual Display
                    (Mode, Note,     │      (Pitch, Status,
                     Settings)       │       Tuning Meter)
                                     │
                          ┌──────────▼──────────┐
                          │                     │
                          │  Chromatic Tuner    │
                          │    Application      │
                          │                     │
                          └──────────┬──────────┘
                                     │
                    ┌────────────────┼────────────────┐
                    │                │                │
              Audio Input      Audio Output    Persistent Storage
              (Microphone)      (Speaker)      (Preferences)
                    │                │                │
         ┌──────────▼──────┐  ┌──────▼──────────┐  ┌─▼──────────────┐
         │                 │  │                 │  │                │
         │  Device Audio   │  │  Device Audio   │  │ Platform Local │
         │  Input System   │  │  Output System  │  │    Storage     │
         │  (Microphone    │  │  (Speaker or    │  │ (UserDefaults/ │
         │   Hardware)     │  │   Headphones)   │  │ SharedPrefs)   │
         │                 │  │                 │  │                │
         └─────────────────┘  └─────────────────┘  └────────────────┘

         Platform Boundary: iOS / Android Operating System
         ════════════════════════════════════════════════════════════
```

**External Entities:**
- **Musician:** Primary user interacting with application via touch, receiving visual feedback
- **Device Audio Input System:** Microphone hardware providing audio samples
- **Device Audio Output System:** Speaker/headphone hardware reproducing reference tones
- **Platform Local Storage:** OS-provided persistent storage for preferences

**Key Interactions:**
- Touch input flows from user to application (mode selection, settings, note choice)
- Visual display flows from application to user (detected pitch, tuning meter, status)
- Audio streams bidirectionally between application and device hardware
- Preferences read/written between application and storage (infrequent)

### B.2 High-Level Architecture Diagram

This diagram illustrates the major subsystems within the Chromatic Tuner application and their relationships.

```
┌───────────────────────────────────────────────────────────────────────┐
│                        Presentation Layer                             │
│  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐     │
│  │  Meter Mode UI   │  │  Sound Mode UI   │  │  Settings UI     │     │
│  │  - Note Display  │  │  - Note Selector │  │  - Pitch Config  │     │
│  │  - Tuning Meter  │  │  - Tone Toggle   │  │  - Help Screen   │     │
│  │  - Status Ind.   │  │  - Status Display│  │  - About         │     │
│  └────────┬─────────┘  └────────┬─────────┘  └────────┬─────────┘     │
└───────────┼─────────────────────┼─────────────────────┼───────────────┘
            │                     │                     │
            │  Display Updates    │  Display Updates    │  Prefs R/W
            │                     │                     │
┌───────────▼─────────────────────▼─────────────────────▼───────────────┐
│                         Application Logic Layer                       │
│  ┌─────────────────────┐  ┌─────────────────────┐  ┌──────────────┐   │
│  │  Pitch Detection    │  │  Tone Generation    │  │  Config Mgr  │   │
│  │  - NSDF/McLeod PPM  │  │  - Sine Synthesis   │  │  - Load/Save │   │
│  │  - Freq → Note      │  │  - Freq Calculation │  │  - Validation│   │
│  │  - Cent Calculation │  │  - Amplitude Control│  │  - Defaults  │   │
│  └──────────┬──────────┘  └──────────┬──────────┘  └──────────────┘   │
└─────────────┼────────────────────────┼────────────────────────────────┘
              │                        │
              │  Process Audio         │  Generate Audio
              │                        │
┌─────────────▼────────────────────────▼────────────────────────────────┐
│                       JUCE Framework Layer                            │
│  ┌──────────────────────┐    ┌────────────────────┐                   │
│  │  Audio Device Mgr    │    │  DSP Utilities     │                   │
│  │  - Device Init       │    │  - Autocorrelation │                   │
│  │  - Callback Routing  │    │  - NSDF Compute    │                   │
│  │  - Buffer Management │    │  - Math Functions  │                   │
│  └──────────┬───────────┘    └────────────────────┘                   │
└─────────────┼─────────────────────────────────────────────────────────┘
              │
              │  Platform Audio API Calls
              │
┌─────────────▼─────────────────────────────────────────────────────────┐
│                   Platform Native Layer                               │
│  ┌──────────────────────────────┐  ┌──────────────────────────────┐   │
│  │  iOS Platform Services       │  │  Android Platform Services   │   │
│  │  - Core Audio (I/O)          │  │  - OpenSL ES / AAudio        │   │
│  │  - AVAudioSession (Config)   │  │  - AudioManager              │   │
│  │  - UserDefaults (Storage)    │  │  - SharedPreferences         │   │
│  │  - UIKit (UI Framework)      │  │  - Android UI Framework      │   │
│  └──────────────────────────────┘  └──────────────────────────────┘   │
└───────────────────────────────────────────────────────────────────────┘
```

**Layer Responsibilities:**
- **Presentation Layer:** User interface rendering, touch event handling, visual feedback
- **Application Logic Layer:** Core algorithms (pitch detection, tone synthesis), business rules, configuration management
- **JUCE Framework Layer:** Cross-platform abstraction for audio I/O, DSP, GUI components
- **Platform Native Layer:** iOS and Android operating system services and APIs

**Design Principles:**
- Separation of concerns: UI separated from logic, logic separated from platform
- JUCE framework provides portability layer minimizing platform-specific code
- Audio processing isolated in real-time thread; UI updates via asynchronous messaging

### B.3 Data Flow Diagram - Pitch Detection (Meter Mode)

This diagram illustrates the flow of data during pitch detection in Meter Mode.

```
┌──────────────┐
│  Instrument  │
│ (Sound Source│
└──────┬───────┘
       │ Acoustic Sound Wave
       ▼
┌──────────────┐
│  Microphone  │
│   Hardware   │
└──────┬───────┘
       │ Analog Electrical Signal
       ▼
┌──────────────────┐
│   Analog-to-     │
│   Digital        │
│   Converter      │
└──────┬───────────┘
       │ Digital Audio Samples (PCM)
       │ 44.1/48 kHz, 16/32-bit
       ▼
┌───────────────────────────────────────────┐
│  Platform Audio Input System              │
│  - Buffer audio samples                   │
│  - Deliver to application callback        │
└──────┬────────────────────────────────────┘
       │ Audio Input Buffer (256-512 samples)
       ▼
┌───────────────────────────────────────────┐
│  JUCE Audio Callback (Real-Time Thread)   │
│  - Receive input buffer                   │
│  - Forward to pitch detection             │
└──────┬────────────────────────────────────┘
       │ Audio Buffer
       ▼
┌───────────────────────────────────────────┐
│  Pitch Detection Algorithm (McLeod PPM)   │
│  Step 1: Compute Autocorrelation          │
└──────┬────────────────────────────────────┘
       │ Autocorrelation Function
       ▼
┌───────────────────────────────────────────┐
│  Step 2: Compute NSDF                     │
│  - Normalize autocorrelation              │
└──────┬────────────────────────────────────┘
       │ NSDF Values
       ▼
┌───────────────────────────────────────────┐
│  Step 3: Identify Fundamental Period      │
│  - Find NSDF peaks for period candidates  │
│  - Apply parabolic interpolation          │
│  - Select highest-clarity peak            │
│  - Convert period to frequency            │
└──────┬────────────────────────────────────┘
       │ Fundamental Frequency (Hz), Confidence
       ▼
┌───────────────────────────────────────────┐
│  Step 4: Map Frequency to Note            │
│  - Calculate: note = round(12×log₂(f/fref)│
│  - Determine note name (C, C#, D, ...)    │
│  - Determine octave number (1-8)          │
└──────┬────────────────────────────────────┘
       │ Note Name, Octave Number
       ▼
┌───────────────────────────────────────────┐
│  Step 5: Calculate Cent Deviation         │
│  - Target freq = fref × 2^((n-57)/12)     │
│  - Cents = 1200 × log₂(f_detected/f_target│
└──────┬────────────────────────────────────┘
       │ Cent Deviation (-50 to +50)
       ▼
┌───────────────────────────────────────────┐
│  Step 6: Determine Tuning Status          │
│  - Flat: cents < -5                       │
│  - In Tune: -5 ≤ cents ≤ +5               │
│  - Sharp: cents > +5                      │
└──────┬────────────────────────────────────┘
       │ Tuning Status (Flat/Center/Sharp)
       ▼
┌───────────────────────────────────────────┐
│  Async Message to UI Thread               │
│  - Package results for display            │
│  - Send via lock-free queue or timer      │
└──────┬────────────────────────────────────┘
       │ Display Data: Note, Octave, Cents, Status
       ▼
┌───────────────────────────────────────────┐
│  UI Update (Main Thread)                  │
│  - Update note name label                 │
│  - Update cent value label                │
│  - Animate tuning meter needle            │
│  - Highlight status indicator             │
└──────┬────────────────────────────────────┘
       │
       ▼
┌──────────────┐
│   Display    │
│  (User Sees  │
│ Tuning Info) │
└──────────────┘
```

**Data Transformations:**
1. Physical sound → electrical signal → digital samples
2. Time-domain samples → autocorrelation function → NSDF
3. NSDF → fundamental period (peak detection) → fundamental frequency
4. Frequency → note name and octave (logarithmic mapping)
5. Frequency → cent deviation (logarithmic comparison)
6. Cent deviation → tuning status (threshold comparison)
7. Detection results → visual display (UI update)

**Performance Considerations:**
- Steps 1-6 must complete within audio callback deadline (~5-10 ms)
- Autocorrelation and NSDF computation are most computationally intensive steps; optimized implementation critical
- UI update (Step 7) occurs asynchronously to avoid blocking audio thread

### B.4 Data Flow Diagram - Tone Generation (Sound Mode)

This diagram illustrates the flow of data during reference tone generation in Sound Mode.

```
┌──────────────┐
│     User     │
└──────┬───────┘
       │ Selects Note (e.g., A4)
       ▼
┌───────────────────────────────────────────┐
│  UI Event Handler (Main Thread)           │
│  - Update selected note state             │
└──────┬────────────────────────────────────┘
       │ Selected Note (Enum: C4...C5)
       ▼
┌───────────────────────────────────────────┐
│  User Presses "Play Tone" Toggle          │
└──────┬────────────────────────────────────┘
       │ Activate Tone Generation
       ▼
┌───────────────────────────────────────────┐
│  Tone Generator Initialization            │
│  - Read current reference pitch (fref)    │
│  - Calculate target frequency:            │
│    f_target = fref × 2^((n-9)/12)         │
│    where n = semitones from A4            │
│  - Initialize sine wave phase             │
└──────┬────────────────────────────────────┘
       │ Target Frequency (Hz), Initial Phase
       ▼
┌───────────────────────────────────────────┐
│  JUCE Audio Callback (Real-Time Thread)   │
│  - Receive output buffer (empty)          │
│  - Request samples from tone generator    │
└──────┬────────────────────────────────────┘
       │ Buffer Size (e.g., 512 samples)
       ▼
┌───────────────────────────────────────────┐
│  Sine Wave Synthesis Algorithm            │
│  FOR each sample i in buffer:             │
│    sample[i] = A × sin(2π × f × t + φ)    │
│    where:                                 │
│      A = amplitude (e.g., 0.25)           │
│      f = target frequency (Hz)            │
│      t = current time (i/sample_rate)     │
│      φ = phase accumulator                │
│  - Update phase accumulator for next call │
└──────┬────────────────────────────────────┘
       │ Audio Output Buffer (Synthesized Samples)
       ▼
┌───────────────────────────────────────────┐
│  JUCE Audio Callback Returns Buffer       │
│  - Deliver samples to platform audio      │
└──────┬────────────────────────────────────┘
       │ Audio Output Buffer
       ▼
┌───────────────────────────────────────────┐
│  Platform Audio Output System             │
│  - Queue samples for playback             │
└──────┬────────────────────────────────────┘
       │ Digital Audio Samples (PCM)
       ▼
┌──────────────────┐
│   Digital-to-    │
│   Analog         │
│   Converter      │
└──────┬───────────┘
       │ Analog Electrical Signal
       ▼
┌──────────────┐
│   Speaker    │
│   Hardware   │
└──────┬───────┘
       │ Acoustic Sound Wave
       ▼
┌──────────────┐
│     User     │
│  (Hears Tone)│
└──────────────┘
```

**Data Transformations:**
1. User note selection → note enumeration
2. Note enumeration → target frequency (12-TET calculation)
3. Target frequency → sine wave parameters
4. Sine function evaluation → audio samples
5. Digital samples → analog signal → acoustic sound

**Key Parameters:**
- **Amplitude:** Fixed at moderate level (e.g., 0.25 normalized = -12 dBFS)
- **Frequency:** Calculated from reference pitch and note offset
- **Phase:** Accumulated across buffer calls for continuous waveform
- **Sample Rate:** Matches platform (44.1 or 48 kHz)

**Performance Considerations:**
- Sine wave synthesis very efficient (simple arithmetic per sample)
- Phase accumulation must maintain precision to prevent frequency drift
- Fade-in/fade-out envelopes applied when starting/stopping to prevent clicks

### B.5 State Machine Diagram - Application Modes

This state diagram illustrates the application's mode transitions and behaviors.

```
                    ┌──────────────┐
                    │  App Launch  │
                    │   (Initial)  │
                    └──────┬───────┘
                           │
                           │ Initialize Audio System
                           │ Load Preferences
                           │
                           ▼
                  ┌────────────────────┐
                  │   Meter Mode       │◄────────────┐
                  │   (Default Mode)   │             │
                  └────────┬───────────┘             │
                           │                         │
      User plays instrument│                         │
                           │                         │
                  ┌────────▼───────────┐             │
                  │  Pitch Detection   │             │
                  │     Active         │             │
                  │  - Monitor mic     │             │
                  │  - Analyze audio   │             │
                  │  - Update display  │             │
                  └────────┬───────────┘             │
                           │                         │
         User taps "Sound" │                         │
              mode button  │                         │
                           │                         │
                           ▼                         │
                  ┌────────────────────┐             │
                  │   Sound Mode       │             │
                  │  (Tone Selection)  │             │
                  └────────┬───────────┘             │
                           │                         │
             User selects  │                         │
                 note      │                         │
                           ▼                         │
                  ┌────────────────────┐             │
                  │  Note Selected     │             │
                  │ (Tone Inactive)    │             │
                  └────────┬───────────┘             │
                           │                         │
           User taps "Play"│                         │
                           │                         │
                           ▼                         │
                  ┌────────────────────┐             │
                  │  Tone Generation   │             │
                  │     Active         │             │
                  │ - Generate sine    │             │
                  │ - Output to speaker│             │
                  └────────┬───────────┘             │
                           │                         │
     User taps "Stop" or   │                         │
     changes note          │                         │
                           │                         │
                           ▼                         │
                  ┌────────────────────┐             │
                  │  Note Selected     │             │
                  │ (Tone Inactive)    │             │
                  └────────┬───────────┘             │
                           │                         │
         User taps "Meter" │                         │
              mode button  │                         │
                           │                         │
                           └─────────────────────────┘


         ┌──────────────────────────────────────────┐
         │         From Any State Above             │
         └──────────────────┬───────────────────────┘
                            │
          User taps Settings│
                            │
                            ▼
                   ┌────────────────────┐
                   │  Settings Screen   │
                   │  - Adjust ref pitch│
                   │  - View help       │
                   │  - See about info  │
                   └────────┬───────────┘
                            │
              User taps Back│
                            │
                            ▼
                   ┌────────────────────┐
                   │  Return to         │
                   │  Previous Mode     │
                   │  (Meter or Sound)  │
                   └────────────────────┘
```

**State Descriptions:**

1. **App Launch:** Initial state; performs initialization
2. **Meter Mode / Pitch Detection Active:** Default operational state; microphone monitoring
3. **Sound Mode / Note Selected (Inactive):** User has selected reference note; tone not playing
4. **Sound Mode / Tone Generation Active:** Continuous sine wave output; pitch detection suspended
5. **Settings Screen:** Configuration and help access; audio processing paused

**Transitions:**

- **Meter ↔ Sound:** Mode selector control in UI
- **Note Selected → Tone Active:** "Play" toggle button
- **Tone Active → Note Selected:** "Stop" toggle button or note change
- **Any Mode → Settings:** Settings button
- **Settings → Previous Mode:** Back/close button

**Concurrent States:**
- Orientation (Portrait / Landscape) exists orthogonally to mode states
- Background/Foreground state affects all modes (audio suspended in background)

### B.6 Use Case Diagram

This diagram illustrates the primary use cases and actors interacting with the system.

```
                                     ┌────────────────────────────┐
                                     │   Chromatic Tuner App      │
                                     │                            │
  ┌──────────────┐                  │  ┌──────────────────────┐  │
  │              │                  │  │  UC-1: Detect Pitch  │  │
  │   Amateur    │──────────────────┼─▶│  and Display Tuning  │  │
  │   Musician   │                  │  │  Status (Meter Mode) │  │
  │              │                  │  └──────────────────────┘  │
  └──────┬───────┘                  │                            │
         │                          │  ┌──────────────────────┐  │
         │                          │  │  UC-2: Generate      │  │
         │    ┌──────────────┐      │  │  Reference Tone      │  │
         └────│              │      │  │  (Sound Mode)        │  │
              │ Professional │──────┼─▶└──────────────────────┘  │
         ┌────│  Musician    │      │                            │
         │    │              │      │  ┌──────────────────────┐  │
         │    └──────────────┘      │  │  UC-3: Calibrate     │  │
         │                          │  │  Reference Pitch     │  │
         │                          │  │  (Settings)          │  │
  ┌──────▼───────┐                  │  └──────────────────────┘  │
  │              │                  │                            │
  │    Music     │                  │  ┌──────────────────────┐  │
  │   Educator   │──────────────────┼─▶│  UC-4: Access Help   │  │
  │              │                  │  │  Documentation       │  │
  └──────────────┘                  │  └──────────────────────┘  │
                                     │                            │
                                     │  ┌──────────────────────┐  │
                                     │  │  UC-5: Switch        │  │
                                     │  │  Between Portrait    │  │
                                     │  │  and Landscape       │  │
                                     │  └──────────────────────┘  │
                                     │                            │
                                     └────────────────────────────┘
```

**Primary Use Cases:**

**UC-1: Detect Pitch and Display Tuning Status**
- Actor: All user classes
- Precondition: Microphone permission granted
- Main flow: User plays instrument → App detects pitch → Displays note, cent deviation, tuning status
- Postcondition: User knows if instrument is flat, in tune, or sharp

**UC-2: Generate Reference Tone**
- Actor: All user classes
- Precondition: None
- Main flow: User switches to Sound Mode → Selects note → Presses play → Hears reference tone
- Postcondition: User has auditory reference for tuning by ear

**UC-3: Calibrate Reference Pitch**
- Actor: Professional musicians (primarily)
- Precondition: None
- Main flow: User opens Settings → Adjusts reference pitch (A4) → Returns to tuning
- Postcondition: All frequencies recalculated based on new reference

**UC-4: Access Help Documentation**
- Actor: Amateur musicians, educators
- Precondition: None
- Main flow: User taps Help button → Reads explanations → Returns to application
- Postcondition: User better understands concepts (cents, note names, calibration)

**UC-5: Switch Device Orientation**
- Actor: All user classes
- Precondition: None
- Main flow: User rotates device → App redraws UI in new orientation → Functionality preserved
- Postcondition: User continues tuning in preferred orientation

**Actor Relationships:**
- All actors can perform all use cases
- Professional musicians more likely to use UC-3 (calibration)
- Amateur musicians more likely to use UC-4 (help)
- Music educators use all features for teaching demonstrations

---

**End of Software Requirements Specification**