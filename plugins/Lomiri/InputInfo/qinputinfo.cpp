/****************************************************************************
**
** Copyright (C) 2014 Canonical Ltd. and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSystems module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qinputinfo.h"

#if defined(LOMIRI_MOCKS)
#include "qinputdeviceinfo_mock_p.h"
#elif defined(Q_OS_LINUX)
#include "linux/qinputdeviceinfo_linux_p.h"
#endif

Q_GLOBAL_STATIC(QInputDeviceManagerPrivate, inputDeviceManagerPrivate)

QT_BEGIN_NAMESPACE

QInputDeviceManagerPrivate * QInputDeviceManagerPrivate::instance()
{
    QInputDeviceManagerPrivate *priv = inputDeviceManagerPrivate();
    return priv;
}

QInputDevicePrivate::QInputDevicePrivate(QObject *parent) :
    QObject(parent),
    type(LomiriInputDevice::Unknown)
{
}

LomiriInputDevice::LomiriInputDevice(QObject *parent) :
    QObject(parent),
    d_ptr(new QInputDevicePrivate(this))
{
}

/*
 * Returns the name of this input device.
 */
QString LomiriInputDevice::name() const
{
    return d_ptr->name;
}

/*
 * Sets the name of this input device to \b name.
 */
void LomiriInputDevice::setName(const QString &name)
{
    d_ptr->name = name;
}

/*
 * Returns the device path of this device.
 */
QString LomiriInputDevice::devicePath() const
{
    return d_ptr->devicePath;
}

/*
 * Sets the device ppath of this device to /b path.
 */
void LomiriInputDevice::setDevicePath(const QString &path)
{
    d_ptr->devicePath = path;
}

/*
 * Returns the number of buttons this device has.
 */
QList <int> LomiriInputDevice::buttons() const
{
    return d_ptr->buttons;
}

/*
 * Adds a button
 */
void LomiriInputDevice::addButton(int buttonCode)
{
    d_ptr->buttons.append(buttonCode);
}

/*
 * Returns the number of switch of this device.
 */
QList <int> LomiriInputDevice::switches() const
{
    return d_ptr->switches;
}

/*
 * Adds a switch
 */
void LomiriInputDevice::addSwitch(int switchCode)
{
    d_ptr->switches.append(switchCode);
}

/*
 * Returns a list of the relative axis of this device
 */
QList <int> LomiriInputDevice::relativeAxis() const
{
    return d_ptr->relativeAxis;
}

/*
 */
void LomiriInputDevice::addRelativeAxis(int axisCode)
{
    d_ptr->relativeAxis.append(axisCode);
}

/*
 * Returns a list of the absolute axis of this device
 */
QList <int> LomiriInputDevice::absoluteAxis() const
{
    return d_ptr->absoluteAxis;
}

/*
 */
void LomiriInputDevice::addAbsoluteAxis(int axisCode)
{
    d_ptr->absoluteAxis.append(axisCode);
}

/*
 * Returns a QInputDevice::InputTypeFlags of all the types of types.
 */
LomiriInputDevice::InputTypeFlags LomiriInputDevice::type() const
{
    return d_ptr->type;
}

/*
 */
void LomiriInputDevice::setType(LomiriInputDevice::InputTypeFlags type) //? setTypes?
{
    d_ptr->type = type;
}

QInputDeviceManager::QInputDeviceManager(QObject *parent) :
    QObject(parent),
    d_ptr(inputDeviceManagerPrivate)
{
    connect(d_ptr, &QInputDeviceManagerPrivate::deviceAdded,this,&QInputDeviceManager::addedDevice);
    connect(d_ptr, &QInputDeviceManagerPrivate::deviceRemoved,this,&QInputDeviceManager::deviceRemoved);

    connect(d_ptr,SIGNAL(ready()),this,SIGNAL(ready()));
}

/*
 * Returns a QMap of known input devices.
 */
QMap <QString, LomiriInputDevice *> QInputDeviceManager::deviceMap()
{
    return d_ptr->deviceMap;
}

/*
 */
void QInputDeviceManager::addedDevice(const QString & devicePath)
{
    Q_EMIT deviceAdded(devicePath);
}

/*
 * Returns a QVector of InputDevices of type filter
 * */
QVector <LomiriInputDevice *> QInputDeviceManager::deviceListOfType(LomiriInputDevice::InputType filter)
{
    QVector <LomiriInputDevice *> dList;
    QMapIterator<QString, LomiriInputDevice *> i(d_ptr->deviceMap);
    while (i.hasNext()) {
        i.next();
        if (i.value()->type().testFlag(filter) || filter == LomiriInputDevice::Unknown) {
            dList.append(i.value());
        }
    }
    return dList;
}

/*
 * Returns the number of input devices with the currently set QInputDevice::InputType filter.
 * If no device filter has been set, returns number of all available input devices.
 * If filter has not been set, returns all available input devices
 */
int QInputDeviceManager::deviceCount() const
{
    return deviceCount(static_cast< LomiriInputDevice::InputType >(d_ptr->currentFilter));
}

/*
 * Returns the number of input devices of the type filter.
 */
int QInputDeviceManager::deviceCount(const LomiriInputDevice::InputType filter) const
{
    int dList = 0;
    QMapIterator<QString, LomiriInputDevice *> i(d_ptr->deviceMap);
    while (i.hasNext()) {
        i.next();
//        qDebug() << i.value()->name() << i.value()->devicePath();
//        qDebug() << i.value()->type() << i.value()->type().testFlag(filter);

        if (i.value()->type().testFlag(filter)) {
            dList++;
        }
    }
    return dList;
}

/*
 * Returns the currently set device filter.
 * */
LomiriInputDevice::InputType QInputDeviceManager::deviceFilter()
{
    return d_ptr->currentFilter;
}

/*
 * Sets the current  input device filter to filter.
 * */
void QInputDeviceManager::setDeviceFilter(LomiriInputDevice::InputType filter)
{
    if (filter !=  d_ptr->currentFilter) {
     d_ptr->currentFilter = filter;
     Q_EMIT deviceFilterChanged(filter);
    }
}

QT_END_NAMESPACE
