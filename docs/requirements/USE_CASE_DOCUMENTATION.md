# Use Case Documentation

## Chromatic Tuner Mobile Application

**Document Version:** 1.0  
**Date:** December 10, 2025  
**Author:** Requirements Engineering Team  
**Project:** Chromatic Tuner Mobile Application

---

## 1. Use Case List

| Primary Actor | Use Cases |
|---------------|-----------|
| Musician | UC-001: Tune Instrument Using Meter Mode |
| | UC-002: Generate Reference Tone Using Sound Mode |
| | UC-003: Calibrate Reference Pitch |
| | UC-004: Switch Between Operating Modes |
| | UC-005: Select Reference Tone Note |
| | UC-006: Grant Microphone Permission |
| | UC-007: Access Help Documentation |
| | UC-008: Rotate Device Orientation |

---

## 2. Detailed Use Cases

### UC-001: Tune Instrument Using Meter Mode

**Author:** Requirements Engineering Team  
**Date Created:** December 10, 2025

**Primary Actor:** Musician

**Secondary Actors:** 
- Device microphone hardware
- Platform audio input system

**Description:**  
The musician plays their instrument while the application continuously detects the pitch, identifies the note, calculates cent deviation from the target frequency, and displays tuning status through an analog-style meter with visual indicators showing whether the instrument is flat, in tune, or sharp.

**Trigger:**  
Musician launches application (opens in Meter Mode by default) or switches to Meter Mode from Sound Mode.

**Preconditions:**
- Application is installed and launched
- Microphone permission has been granted
- Device microphone is functional
- Application is in foreground

**Postconditions:**
- Musician knows whether instrument is flat, in tune, or sharp
- Musician knows detected note name and octave
- Musician knows precise cent deviation for fine tuning

**Basic Flow:**

1. Musician ensures application is in Meter Mode (default on launch)
2. Musician positions device 30-100 cm from instrument sound source
3. Musician plays single note on instrument
4. Application captures audio through microphone
5. Application analyzes audio using FFT-based pitch detection
6. Application identifies fundamental frequency
7. Application maps frequency to nearest chromatic note (C through B with octave 1-8)
8. Application calculates cent deviation from target frequency based on current reference pitch
9. Application updates display showing:
   - Note name and octave (large text, e.g., "A4")
   - Cent deviation value (numeric, e.g., "-12.3 cents")
   - Tuning meter needle position indicating deviation
   - Status indicator ("FLAT", "IN TUNE", or "SHARP")
10. Musician adjusts instrument tuning based on visual feedback
11. Steps 3-10 repeat continuously as musician plays and adjusts
12. When meter shows "IN TUNE" (within ±5 cents), musician stops adjusting

**Alternative Flows:**

**AF-001: Low Signal Level**
- At step 4, if audio level is below -40 dBFS threshold:
  - Application displays "No Signal" or equivalent message
  - Note display shows "—" or "•••"
  - Meter needle remains centered or hidden
  - User moves device closer or plays louder
  - Resume at step 3

**AF-002: Ambiguous Detection**
- At step 6, if multiple frequency candidates have similar confidence:
  - Application rejects detection as unreliable
  - Display shows "No Signal" or inactive state
  - User ensures quieter environment or clearer tone
  - Resume at step 3

**AF-003: Note Change During Sustained Pitch**
- At step 7, if detected note differs from previous detection:
  - Application waits 100ms to confirm new note is stable
  - If confirmed, updates note display
  - If unstable, maintains previous note display
  - Continue with step 8

**AF-004: Reference Pitch Changed Mid-Session**
- Between any steps, if user modifies reference pitch in settings:
  - Application immediately recalculates target frequencies
  - Cent deviation updates based on new reference
  - Continue with current step

**Exceptions:**

**EX-001: Microphone Permission Denied**
- Application detects permission status is "denied"
- Displays message: "Microphone access required for pitch detection"
- Provides "Open Settings" button linking to system settings
- Meter Mode remains inactive until permission granted

**EX-002: Audio System Initialization Failure**
- Audio device fails to initialize at step 4
- Displays error: "Unable to access audio. Please check permissions and restart."
- Provides "Retry" button to attempt reinitialization
- If retry fails, user must restart application

**EX-003: Application Backgrounded**
- If application enters background during any step:
  - Audio processing automatically suspends
  - Display freezes at last known state
  - When returning to foreground, resume at step 3

**EX-004: Excessive Background Noise**
- At step 5, if signal-to-noise ratio insufficient for reliable detection:
  - Application displays "No Signal" or shows highly unstable readings
  - User moves to quieter location
  - Resume at step 3

**Priority:** CRITICAL (Core functionality)

**Business Rules:**

| ID | Rule | Type | Static/Dynamic |
|----|------|------|----------------|
| BR-001 | Detection range must span C1 (32.70 Hz) to C8 (4186.01 Hz) | Constraint | Static |
| BR-002 | Detection accuracy must be within ±1 cent for signals ≥40 dB SNR | Quality | Static |
| BR-003 | Pitch detection latency must not exceed 30ms on 90% of devices | Performance | Static |
| BR-004 | Display update rate must be minimum 20 Hz | Performance | Static |
| BR-005 | "IN TUNE" zone defined as ±5 cents from target frequency | Business Logic | Static |
| BR-006 | Note persistence requires 100ms stability before display change | Business Logic | Static |
| BR-007 | All frequencies calculated based on current reference pitch (A4) | Computation | Dynamic |
| BR-008 | Microphone permission required for Meter Mode operation | Authorization | Static |

**Assumptions:**
- Device microphone has frequency response covering 60-4000 Hz minimum
- User understands basic music terminology (note names) or will consult help
- Ambient noise level permits signal-to-noise ratio ≥40 dB
- User tunes one string/note at a time (monophonic detection only)
- Device has sufficient CPU for real-time FFT processing

**Other Information:**
- Pure interval reference marks at -13.7 cents (pure major third) and +15.6 cents (pure minor third) provide educational reference for historical temperaments
- Professional musicians may prefer numeric cent display; amateur musicians rely more on visual meter and status indicators
- Meter needle uses damping algorithm to reduce jitter while remaining responsive to genuine pitch changes

---

### UC-002: Generate Reference Tone Using Sound Mode

**Author:** Requirements Engineering Team  
**Date Created:** December 10, 2025

**Primary Actor:** Musician

**Secondary Actors:**
- Device speaker/audio output hardware
- Platform audio output system

**Description:**  
The musician selects a reference note from a one-octave range (C4 to C5) and activates continuous sine wave tone generation to provide an auditory pitch reference for tuning by ear.

**Trigger:**  
Musician switches to Sound Mode and presses tone generation toggle control.

**Preconditions:**
- Application is installed and launched
- Application is in foreground
- Device audio output is functional

**Postconditions:**
- Selected reference tone plays continuously at precise frequency
- Musician has auditory reference for matching instrument pitch
- Tone generation ceases when toggle deactivated or mode switched

**Basic Flow:**

1. Musician taps "Sound" mode selector control
2. Application switches from Meter Mode to Sound Mode
3. Application displays note selection interface (virtual keyboard or button grid)
4. Application displays current reference pitch setting (e.g., "A4 = 440 Hz")
5. Musician taps desired reference note (e.g., A4)
6. Application highlights selected note visually
7. Musician taps "Play Tone" toggle button
8. Application calculates target frequency: f = f_ref × 2^((n-9)/12) where n is semitones from A4
9. Application initializes sine wave synthesis with calculated frequency
10. Application generates continuous pure sine wave tone through speakers
11. Application updates toggle button to "Stop Tone" state with visual indication
12. Musician listens to reference tone and matches instrument pitch by ear
13. When finished, musician taps "Stop Tone" toggle button
14. Application applies fade-out envelope (5-10ms) and ceases tone generation
15. Toggle button returns to "Play Tone" state

**Alternative Flows:**

**AF-001: Change Note While Tone Playing**
- At step 12, musician taps different note:
  - Application crossfades from current frequency to new frequency (50-100ms)
  - New note becomes highlighted
  - Tone continues at new frequency
  - Resume at step 12

**AF-002: Reference Pitch Changed While Tone Playing**
- At step 12, musician changes reference pitch in settings:
  - Application recalculates frequency based on new reference
  - Smoothly transitions to new frequency (100ms)
  - Tone continues at new frequency
  - Resume at step 12

**AF-003: Switch to Meter Mode While Tone Playing**
- At step 12, musician taps "Meter" mode selector:
  - Application immediately stops tone generation
  - Switches to Meter Mode interface
  - Pitch detection becomes active
  - Use case terminates

**Exceptions:**

**EX-001: Audio Output Failure**
- At step 10, audio output system fails:
  - Display error: "Unable to generate audio. Please check volume and restart."
  - Provides "Retry" button
  - If retry fails, user must restart application

**EX-002: Application Backgrounded During Playback**
- If application enters background during step 12:
  - Tone generation automatically stops
  - When returning to foreground, toggle returns to "Play Tone" state
  - User must manually reactivate if desired

**EX-003: External Audio Route Change**
- At step 12, user connects/disconnects headphones:
  - Audio route changes (speaker to headphones or vice versa)
  - Tone generation continues on new output
  - Brief interruption <100ms may occur

**Priority:** CRITICAL (Core functionality)

**Business Rules:**

| ID | Rule | Type | Static/Dynamic |
|----|------|------|----------------|
| BR-009 | Reference tone range limited to C4 (261.63 Hz) to C5 (523.25 Hz) | Constraint | Static |
| BR-010 | Tone generation accuracy must be within ±1.5 cents | Quality | Static |
| BR-011 | Generated tones must be pure sine waves (no harmonics) | Technical | Static |
| BR-012 | Tone activation latency must not exceed 10ms | Performance | Static |
| BR-013 | Amplitude must remain constant within ±0.5 dB during playback | Quality | Static |
| BR-014 | Fade-in/fade-out envelopes required to prevent clicking artifacts | Technical | Static |
| BR-015 | Tone generation and pitch detection cannot operate simultaneously | Business Logic | Static |
| BR-016 | All tone frequencies calculated from current reference pitch | Computation | Dynamic |

**Assumptions:**
- Device speakers can reproduce 200-600 Hz range with acceptable quality
- User has set device volume to comfortable listening level
- User understands concept of matching pitch by ear
- Quiet environment permits hearing tone clearly

**Other Information:**
- Musicians preferring aural tuning may use Sound Mode exclusively
- Music educators use Sound Mode for group tuning demonstrations
- Note selection interface may resemble piano keyboard for intuitive mapping

---

### UC-003: Calibrate Reference Pitch

**Author:** Requirements Engineering Team  
**Date Created:** December 10, 2025

**Primary Actor:** Musician (primarily professionals)

**Description:**  
The musician adjusts the A4 reference pitch frequency from default 440 Hz to accommodate regional variations (e.g., 442 Hz orchestral), historical performance practices (e.g., 415 Hz Baroque), or personal preferences.

**Trigger:**  
Musician taps settings control and navigates to reference pitch calibration.

**Preconditions:**
- Application is installed and launched
- Settings screen is accessible from current mode

**Postconditions:**
- Reference pitch stored persistently
- All frequency calculations update based on new reference
- Pitch detection and tone generation use new reference immediately

**Basic Flow:**

1. Musician taps settings (gear icon) from any mode
2. Application displays Settings screen showing "Reference Pitch (A4)"
3. Application displays current value (e.g., "440 Hz")
4. Musician taps "−" button one or more times to decrease frequency
5. Application decrements reference pitch by 1 Hz per tap
6. Application updates display showing new value
7. OR: Musician taps "+" button one or more times to increase frequency
8. Application increments reference pitch by 1 Hz per tap
9. Application updates display showing new value
10. Application immediately recalculates all note frequencies based on new reference
11. If returning to Meter Mode, cent deviations reflect new reference
12. If returning to Sound Mode with active tone, frequency updates smoothly
13. Musician taps back/close button
14. Application returns to previous mode (Meter or Sound)
15. Application persists new reference pitch to local storage

**Alternative Flows:**

**AF-001: Reset to Default**
- At step 4 or 8, musician taps "Reset to 440 Hz" button:
  - Application sets reference pitch to 440 Hz
  - Display updates to show "440 Hz"
  - Resume at step 10

**AF-002: Reach Minimum Bound**
- At step 5, if reference pitch is 410 Hz:
  - "−" button becomes disabled or visually indicates limit
  - Additional taps have no effect
  - Musician must tap "+" to increase

**AF-003: Reach Maximum Bound**
- At step 9, if reference pitch is 480 Hz:
  - "+" button becomes disabled or visually indicates limit
  - Additional taps have no effect
  - Musician must tap "−" to decrease

**Exceptions:**

**EX-001: Storage Write Failure**
- At step 15, persistent storage fails:
  - Setting remains active for current session
  - Warning displayed: "Unable to save setting"
  - Reverts to default 440 Hz on next application launch

**Priority:** HIGH

**Business Rules:**

| ID | Rule | Type | Static/Dynamic |
|----|------|------|----------------|
| BR-001 | Reference pitch A4 must be between 410-480 Hz inclusive | Constraint | Static |
| BR-017 | Reference pitch adjustment increments must be 1 Hz | Business Logic | Static |
| BR-018 | Default reference pitch is 440 Hz on first launch | Business Logic | Static |
| BR-019 | Reference pitch changes apply immediately without restart | Technical | Static |
| BR-020 | Reference pitch must persist across application launches | Technical | Static |

**Assumptions:**
- User understands concept of reference pitch calibration
- User knows desired reference frequency (e.g., 442 Hz for orchestra)
- Changes to reference pitch are infrequent (not adjusted mid-tuning)

---

### UC-004: Switch Between Operating Modes

**Description:**  
Musician switches between Meter Mode (pitch detection) and Sound Mode (reference tone generation) using mode selector control.

**Basic Flow:**

1. Musician views mode selector showing "Meter" and "Sound" options
2. Musician taps desired mode
3. Application switches interface to selected mode
4. If switching from Sound Mode with active tone, tone generation stops
5. If switching to Meter Mode, pitch detection becomes active

**Exceptions:**

**EX-001:** If audio system fails during mode switch, displays error and provides retry option.

**Priority:** CRITICAL

---

### UC-005: Select Reference Tone Note

**Description:**  
In Sound Mode, musician selects which chromatic note (C4 through C5) to use as reference tone before activating playback.

**Basic Flow:**

1. Musician is in Sound Mode with note selection interface visible
2. Musician taps desired note on virtual keyboard or button grid
3. Application highlights selected note visually
4. Selected note becomes active for tone generation when toggle pressed

**Priority:** HIGH

---

### UC-006: Grant Microphone Permission

**Description:**  
On first launch or after permission denial, musician grants microphone access required for pitch detection functionality.

**Basic Flow:**

1. Application detects microphone permission status is "not determined"
2. Application displays platform permission dialog with explanation
3. Musician taps "Allow" in permission dialog
4. Platform grants microphone access to application
5. Meter Mode becomes functional for pitch detection

**Exceptions:**

**EX-001: Permission Denied**
- If musician taps "Don't Allow":
  - Meter Mode displays message explaining microphone requirement
  - Provides "Open Settings" button linking to system settings
  - Sound Mode remains functional

**Priority:** CRITICAL

---

### UC-007: Access Help Documentation

**Description:**  
Musician accesses in-app help to learn about note names, cent deviation, reference pitch calibration, and usage tips.

**Basic Flow:**

1. Musician taps help control (question mark icon)
2. Application displays help screen with sections:
   - Chromatic scale reference
   - Cents explanation
   - Pure interval marks explanation  
   - Reference pitch explanation
   - Usage tips
3. Musician reads relevant sections
4. Musician taps back/close button
5. Application returns to previous screen

**Priority:** MEDIUM

---

### UC-008: Rotate Device Orientation

**Description:**  
Musician rotates device between portrait and landscape orientations; application adapts interface layout automatically.

**Basic Flow:**

1. Musician physically rotates device
2. Platform detects orientation change
3. Application recalculates layout geometry for new orientation
4. Application redraws interface within 200ms
5. All functionality remains accessible
6. Audio processing continues uninterrupted

**Priority:** HIGH

---

## 3. Business Rules

| ID | Rule Definition | Type of Rule | Static or Dynamic | Source |
|----|-----------------|--------------|-------------------|--------|
| BR-001 | Reference pitch A4 must be between 410-480 Hz inclusive | Constraint | Static | Requirements Specification |
| BR-002 | Detection accuracy must be within ±1 cent for signals ≥40 dB SNR | Quality Standard | Static | Requirements Specification |
| BR-003 | Reference tone accuracy must be within ±1.5 cents | Quality Standard | Static | Requirements Specification |
| BR-004 | Pitch detection latency must not exceed 30ms on 90% of supported devices | Performance | Static | Requirements Specification |
| BR-005 | Tuning status "IN TUNE" defined as ±5 cents from target frequency | Business Logic | Static | Requirements Specification |
| BR-006 | Detected note must remain stable for 100ms before display updates | Business Logic | Static | Design Decision |
| BR-007 | All note frequencies calculated using 12-tone equal temperament: f(n) = f_ref × 2^((n-57)/12) | Computation | Static | Music Theory |
| BR-008 | Pitch detection and tone generation cannot operate simultaneously | Business Logic | Static | Technical Constraint |
| BR-009 | Reference tone range limited to C4 (261.63 Hz) through C5 (523.25 Hz) | Constraint | Static | Hardware Limitation |
| BR-010 | Microphone permission required for Meter Mode; Sound Mode functional without it | Authorization | Static | Platform Requirement |
| BR-011 | Application must function 100% offline without network connectivity | Operational | Static | Business Requirement |
| BR-012 | Reference pitch changes apply immediately to all calculations without restart | Technical | Static | User Experience |
| BR-013 | Detection frequency range spans C1 (32.70 Hz) to C8 (4186.01 Hz) | Constraint | Static | Requirements Specification |
| BR-014 | Display update rate must be minimum 20 Hz (50ms refresh) | Performance | Static | Requirements Specification |
| BR-015 | Audio processing automatically suspends when application backgrounded | Technical | Static | Platform Requirement |

---

**End of Use Case Documentation**