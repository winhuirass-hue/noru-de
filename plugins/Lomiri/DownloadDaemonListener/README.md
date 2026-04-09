# DownloadDaemonListener Plugin

Qt 6.8.2 port of the DownloadDaemonListener plugin from Lomiri. Provides DBus/QML access to the Lomiri Download Daemon for tracking download progress and managing download operations.

**Qt Version**: 6.8.2

**Platform**: Ubuntu 24.04.3 LTS

---

## Overview

Manages download tracking in Lomiri through a DBus service. Allows applications to monitor download progress, handle completion, pause, resume, and error events from the Lomiri Download Daemon. Provides QML access to retrieve and track download information via DBus.

---

## Build

### Requirements

- Qt 6.8.2
- CMake 3.17+
- Linux with DBus
- ldm-common-qt6 library

### Dependencies

**ldm-common Package (Qt6 Port)**

The `ldm-common` package does not have an official Qt6 version available. To resolve this dependency:
1. Cloned the Qt5 source code for ldm-common
2. Ported the codebase to Qt6
3. Built and installed the Qt6 version of ldm-common

This allows the DownloadDaemonListener plugin to compile and function correctly with Qt6.

### Build Plugin

```bash
cd plugins/Lomiri/DownloadDaemonListener
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=~/Qt/6.8.2/gcc_64
make
```

Output: `libDownloadDaemonListener.so`, `libDownloadDaemonListenerplugin.so`, `qmldir`

### Build QML Tests

```bash
cd plugins/Lomiri/DownloadDaemonListener/Tests/QMLTests
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=~/Qt/6.8.2/gcc_64
make
./appQMLTests
```

### Build Unit Tests

```bash
cd plugins/Lomiri/DownloadDaemonListener/Tests/UnitTests
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=~/Qt/6.8.2/gcc_64
make
ctest --verbose
```

---

## API

### DownloadTracker (QML_ELEMENT)

Main class for tracking download progress via DBus connection.

**Properties:**

| Property | Type | Access | Description |
|----------|------|--------|-------------|
| `service` | QString | Read/Write | DBus service name (e.g., "com.ubuntu.downloads") |
| `dbusPath` | QString | Read/Write | DBus object path (e.g., "/com/ubuntu/downloads/1") |
| `serviceReady` | bool | Read-only | Indicates if DBus service is connected and ready |

**Methods:**

| Method | Arguments | Returns | Description |
|--------|-----------|---------|-------------|
| `setService(service)` | QString service | void | Set the DBus service name |
| `setDbusPath(path)` | QString path | void | Set the DBus object path |
| `service()` | - | QString | Get the current service name |
| `dbusPath()` | - | QString | Get the current DBus path |
| `isServiceReady()` | - | bool | Check if service is ready |

**Signals:**

| Signal | Arguments | Description |
|--------|-----------|-------------|
| `serviceChanged` | QString service | Emitted when service property changes |
| `dbusPathChanged` | QString dbusPath | Emitted when dbusPath property changes |
| `serviceReadyChanged` | bool ready | Emitted when service ready state changes |
| `started` | bool success | Emitted when download starts |
| `progress` | qulonglong received, qulonglong total | Emitted periodically with download progress |
| `paused` | bool success | Emitted when download is paused |
| `resumed` | bool success | Emitted when download resumes |
| `canceled` | bool success | Emitted when download is canceled |
| `finished` | QString path | Emitted when download completes |
| `error` | QString error | Emitted on download error |
| `processing` | QString path | Emitted when download is being processed |

---

## Qt5 to Qt6 Migration

### CMakeLists.txt

**Key Changes:**

- Replaced `add_library(MODULE)` + `add_lomiri_plugin()` with `qt_add_qml_module()`
- Changed `find_package(Qt5 ...)` to `find_package(Qt6 ...)`
- Changed `target_link_libraries()` from `Qt5::` to `Qt6::` targets with `PRIVATE` keyword
- `qt_add_qml_module()` automatically generates `qmldir`

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

---

## Testing

### QML Testing

Test project located in `Tests/QMLTests/`. Automatically discovers plugin build directory and runs tests.

**Tests validate:**
- `DownloadTracker` (creatable from QML)
- Property initialization and access (`service`, `dbusPath`, `serviceReady`)

### Unit Tests

Test files located in `Tests/UnitTests/`. Contains 1 test file.

#### **tst_downloadtracker.cpp**

Tests `DownloadTracker` core functionality:

- ✓ Properties initially empty (`service`, `dbusPath`)
- ✓ Service property getter and setter
- ✓ DBus path property getter and setter
- ✓ `serviceChanged` signal emitted on property change
- ✓ `dbusPathChanged` signal emitted on property change
- ✓ `serviceReadyChanged` signal emitted when service is configured
- ✓ No duplicate signal on unchanged value for service
- ✓ No duplicate signal on unchanged value for dbusPath
- ✓ Properties are independent (one property doesn't affect the other)

**Expected output:**
```
100% tests passed, 0 tests failed
```

---
