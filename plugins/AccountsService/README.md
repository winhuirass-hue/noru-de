# AccountsService Plugin

Qt 6.8.2 port of the AccountsService plugin from Lomiri. Provides QML access to user account settings, authentication properties, and security configurations via DBus.

**Qt Version**: 6.8.2 (required)  
**Platform**: Ubuntu 24.04.3 LTS

---

## Overview

Exposes user account properties and settings from the system AccountsService via DBus. Allows QML applications to read and modify user preferences, security settings, input methods, and UI configurations. This singleton plugin is essential for the Lomiri shell to manage user account settings and security policies.

---

## Build

### Requirements

- Qt 6.8.2
- CMake 3.17+
- Linux with DBus
- libglib2.0-dev (for g_get_user_name)
- dbus-test-runner (for unit tests)

### Build Plugin

```bash
cd plugins/AccountsService
mkdir build && cd build
cmake .. && make
```

Output: `libAccountsService-qml.so`, `libAccountsService-qmlplugin.so`, `qmldir`

### Build QML Tests

```bash
cd plugins/AccountsService/Tests/QMLTests
mkdir build && cd build
cmake .. && make
./appQMLTests
```

### Build Unit Tests

```bash
cd tests/plugins/AccountsService
mkdir build && cd build
cmake .. && make
ctest --verbose
```

---

## API

### Properties (Readable)

| Property | Type | Description |
|----------|------|-------------|
| `user` | string (read/write) | Current user account name |
| `realName` | string (read/write) | User's real/display name |
| `email` | string (read/write) | User's email address |
| `backgroundFile` | string | Path to user's background image |
| `demoEdges` | bool (read/write) | Enable/disable demo edge gestures |
| `demoEdgesCompleted` | list | List of completed demo edges |
| `enableFingerprintIdentification` | bool | Fingerprint authentication enabled |
| `enableLauncherWhileLocked` | bool | Launcher accessible when screen locked |
| `enableIndicatorsWhileLocked` | bool | System indicators visible when locked |
| `hideNotificationContentWhileLocked` | bool | Hide notification details when locked |
| `statsWelcomeScreen` | bool | Show statistics on welcome screen |
| `passwordDisplayHint` | enum | Password input method (0=Keyboard, 1=Numeric) |
| `pinCodePromptManager` | string | PIN code prompt UI manager name |
| `defaultPinCodePromptManager` | string (constant) | Default PIN prompt manager |
| `pincodeLength` | uint | Required PIN code length |
| `failedLogins` | uint (read/write) | Count of failed login attempts |
| `failedFingerprintLogins` | uint (read/write) | Count of failed fingerprint logins |
| `keymaps` | list | Input method keymaps/keyboard layouts |

### Methods (Invokable from QML)

| Method | Parameters | Description |
|--------|-----------|-------------|
| `markDemoEdgeCompleted()` | edge: string | Mark a demo edge gesture as completed |

### Signals

| Signal | Parameters | Description |
|--------|-----------|-------------|
| `userChanged()` | — | Emitted when user account changes |
| `realNameChanged()` | — | Emitted when real name changes |
| `emailChanged()` | — | Emitted when email changes |
| `demoEdgesChanged()` | — | Emitted when demo edges setting changes |
| `demoEdgesCompletedChanged()` | — | Emitted when demo edges completion list changes |
| `enableFingerprintIdentificationChanged()` | — | Emitted when fingerprint setting changes |
| `enableLauncherWhileLockedChanged()` | — | Emitted when launcher lock setting changes |
| `enableIndicatorsWhileLockedChanged()` | — | Emitted when indicators lock setting changes |
| `hideNotificationContentWhileLockedChanged()` | — | Emitted when notification hide setting changes |
| `backgroundFileChanged()` | — | Emitted when background image changes |
| `statsWelcomeScreenChanged()` | — | Emitted when welcome screen stats setting changes |
| `passwordDisplayHintChanged()` | — | Emitted when password display hint changes |
| `pincodeLengthChanged()` | — | Emitted when PIN code length changes |
| `failedLoginsChanged()` | — | Emitted when failed login count changes |
| `failedFingerprintLoginsChanged()` | — | Emitted when failed fingerprint count changes |
| `keymapsChanged()` | — | Emitted when keyboard layouts change |
| `pinCodePromptManagerChanged()` | — | Emitted when PIN prompt manager changes |

---

## Qt5 to Qt6 Migration

### CMakeLists.txt

**Key Changes:**

- Replaced `add_library(MODULE)` + `add_lomiri_plugin()` with `qt_add_qml_module()`
- Changed `find_package(Qt5 ...)` to `find_package(Qt6 ...)`
- Changed `target_link_libraries()` from `Qt5::` to `Qt6::` targets with `PRIVATE` keyword
- `qt_add_qml_module()` automatically generates `qmldir`

**For Individual Plugin Builds:**

`paths.h` is **required** - AccountsService.cpp uses utility functions from it. When building individually, add to CMakeLists.txt:

```cmake
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/paths.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/paths.h"
)

target_include_directories(AccountsService-qml PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
```

This generates `paths.h` from the `paths.h.in` template at build time, making the required functions available to the plugin.

### Header Files

**Pattern (applies to all exposed classes):**

**Qt5 (removed plugin factory code):**
```cpp
// plugin.cpp (DELETED)
void SomePlugin::registerTypes(const char *uri) {
    qmlRegisterType<ClassName>(uri, 1, 0, "ClassName");
    qmlRegisterSingletonType<SingletonClass>(uri, 1, 0, "SingletonClass", ...);
    qmlRegisterUncreatableType<ReadOnlyData>(uri, 1, 0, "ReadOnlyData", "ReadOnlyData cannot be created from QML");
}
```

**Qt6 (macro-based registration):**
```cpp
// Each class header
#include <qqmlintegration.h>

// Regular creatable type
class ClassName: public QObject {
    Q_OBJECT
    QML_ELEMENT     // Can be instantiated from QML
    // ...
};

// Singleton type
class SingletonClass: public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON   // Only one instance, accessible globally
    // ...
};

// Uncreatable type (accessible but cannot be instantiated from QML)
class ReadOnlyData: public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("ReadOnlyData cannot be created from QML")
    // ...
};
```

**Why**: Qt6 uses compile-time macro-based registration instead of runtime type registration. This eliminates runtime overhead, reduces binary size, and removes the need for plugin factory classes.

### Files Deleted

- `plugin.h` — No longer needed (replaced by `QML_ELEMENT` macro)
- `plugin.cpp` — No longer needed (replaced by `QML_ELEMENT` macro)
- `qmldir` — Auto-generated by `qt_add_qml_module()`

### Code Changes in Source Files


**AccountsService.cpp:**

**Bug fix**: Changed signal name from `hideNotificationContentWhileLocked` to `hideNotificationContentWhileLockedChanged` (line 110)
   - Ensures proper Qt signal/slot connections
   - Prevents: `QMetaObject::invokeMethod: No such method` warnings

---

## Testing

### Directory Structure

```
lomiri-qt-6-migration/
│
├── plugins/AccountsService/                    ← Plugin Source Code
│   ├── AccountsService.h
│   ├── AccountsService.cpp
│   ├── AccountsServiceDBusAdaptor.h
│   ├── AccountsServiceDBusAdaptor.cpp
│   ├── CMakeLists.txt
│   ├── README.md (this file)
│   │
│   └── Tests/QMLTests/                         ← QML Example Tests (Custom)
│       ├── CMakeLists.txt
│       ├── main.cpp
│       ├── main.qml
│       └── AccountsService/
│           ├── qmldir
│           ├── libAccountsService-qml.so        ← Core plugin library
│           └── libAccountsService-qmlplugin.so  ← QML plugin wrapper
│
└── tests/plugins/AccountsService/              ← Unit Tests (Lomiri-provided, Qt6 Ported)
    ├── CMakeLists.txt
    ├── AccountsServer.h
    ├── AccountsServer.cpp
    ├── PropertiesServer.h
    ├── PropertiesServer.cpp
    ├── LscServer.h
    ├── LscServer.cpp
    ├── server.cpp
    ├── client.cpp
    ├── types.h
    └── interfaces.xml
```

### Unit Test Configuration (Qt6 Migration)

The unit test CMakeLists.txt has been ported to Qt6 with the following changes:

**Key Changes:**

- Changed `find_package(Qt5 COMPONENTS ...)` to `find_package(Qt6 COMPONENTS ...)`
- Updated `target_link_libraries()` from `Qt5::` to `Qt6::` targets with `PRIVATE` keyword
- **Qt6 Fix**: Added post-processing step to remove `class QStringList;` forward declaration from generated adaptor headers (Qt6 defines QStringList as a using alias, not a class)
- Uses `add_lomiri_unittest` macro when building from project root (defined in `/tests/CMakeLists.txt`)
- Falls back to standalone CMake `add_test()` with `dbus-test-runner` for standalone builds
- Properly sets up environment variables: `QML2_IMPORT_PATH`, `LOMIRI_SOURCE_DIR`, and dbus-test-runner configuration

The CMakeLists.txt checks if the `add_lomiri_unittest` macro is available. If available, it leverages project-wide test configuration; otherwise, it falls back to standalone CMake `add_test()` with dbus-test-runner.

### QML Testing

Test project located in `Tests/QMLTests/`. Automatically discovers plugin build directory and runs tests.

**Tests validate:**
- ✓ Singleton instance accessible from QML as `AccountsService`
- ✓ All 18 Q_PROPERTY properties readable in QML
- ✓ Read/write properties (user, realName, email, etc.) can be accessed
- ✓ Q_INVOKABLE method `markDemoEdgeCompleted()` invocation
- ✓ Console output for property access verification

### Unit Tests

**Tests validate:**
- ✓ All 18 Q_PROPERTY properties (get/set/notify)
- ✓ All 17 property change signals
- ✓ Q_INVOKABLE method: `markDemoEdgeCompleted()`
- ✓ Asynchronous property updates via DBus
- ✓ Signal emissions on property changes
- ✓ Proxy method calls (SystemCompositor integration)
- ✓ Error handling and type conversions
- ✓ Cross-DBus interface communication

**Expected Result**:
```
100% tests passed, 0 tests failed

