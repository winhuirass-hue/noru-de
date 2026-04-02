#include <QtTest>
#include <QSignalSpy>
#include <QVariant>
#include "../../qinputinfo.h"

class TestQInputInfo : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();

    void testDeviceBasics();
    void testManagerCore();
    void testSignals();
    void testPropertiesAndMeta();
    void testFunctionalAPI();
    void testMetaTypeAndInvokable();

private:
    QInputDeviceManager *manager;
};

void TestQInputInfo::initTestCase()
{
    manager = new QInputDeviceManager();
    QVERIFY(manager != nullptr);
}

void TestQInputInfo::cleanupTestCase()
{
    delete manager;
    manager = nullptr;
}

void TestQInputInfo::init()
{
    manager->setDeviceFilter(LomiriInputDevice::Unknown);
}

void TestQInputInfo::testDeviceBasics()
{
    LomiriInputDevice dev;

    QCOMPARE(dev.name(), QString());
    QCOMPARE(dev.devicePath(), QString());

    QVERIFY(dev.buttons().isEmpty());
    QVERIFY(dev.switches().isEmpty());
    QVERIFY(dev.relativeAxis().isEmpty());
    QVERIFY(dev.absoluteAxis().isEmpty());

    QCOMPARE(dev.type(),
             LomiriInputDevice::InputTypeFlags(LomiriInputDevice::Unknown));

    LomiriInputDevice::InputTypeFlags flags;
    flags |= LomiriInputDevice::Mouse;
    flags |= LomiriInputDevice::Keyboard;

    QVERIFY(flags.testFlag(LomiriInputDevice::Mouse));
    QVERIFY(flags.testFlag(LomiriInputDevice::Keyboard));
}

void TestQInputInfo::testManagerCore()
{
    QCOMPARE(manager->deviceFilter(),
             LomiriInputDevice::InputTypeFlags(LomiriInputDevice::Unknown));

    QVERIFY(manager->deviceCount() >= 0);
}

void TestQInputInfo::testSignals()
{
    QSignalSpy spy(manager,
                   SIGNAL(deviceFilterChanged(LomiriInputDevice::InputType)));

    QVERIFY(spy.isValid());

    manager->setDeviceFilter(LomiriInputDevice::Mouse);
    QCOMPARE(spy.count(), 1);

    manager->setDeviceFilter(LomiriInputDevice::Mouse);
    QCOMPARE(spy.count(), 1);

    manager->setDeviceFilter(LomiriInputDevice::Keyboard);
    QCOMPARE(spy.count(), 2);
}

void TestQInputInfo::testPropertiesAndMeta()
{
    QVariant value = manager->property("deviceFilter");
    QVERIFY(value.isValid());

    manager->setProperty("deviceFilter", LomiriInputDevice::Mouse);
    QCOMPARE(manager->deviceFilter(), LomiriInputDevice::Mouse);

    const QMetaObject *meta = manager->metaObject();
    QVERIFY(meta->indexOfProperty("deviceCount") != -1);
    QVERIFY(meta->indexOfProperty("deviceFilter") != -1);
}

void TestQInputInfo::testFunctionalAPI()
{
    int total = manager->deviceCount();
    QVERIFY(total >= 0);

    auto mice = manager->deviceListOfType(LomiriInputDevice::Mouse);
    auto keyboards = manager->deviceListOfType(LomiriInputDevice::Keyboard);

    QVERIFY(mice.size() <= total);
    QVERIFY(keyboards.size() <= total);

    QCOMPARE(mice.size(),
             manager->deviceCount(LomiriInputDevice::Mouse));

    QCOMPARE(keyboards.size(),
             manager->deviceCount(LomiriInputDevice::Keyboard));

    auto map = manager->deviceMap();
    QCOMPARE(map.size(), total);

    for (auto it = map.begin(); it != map.end(); ++it) {
        QVERIFY(!it.key().isEmpty());
        QVERIFY(it.value() != nullptr);
    }
}

void TestQInputInfo::testMetaTypeAndInvokable()
{
    QVariant var = QVariant::fromValue(LomiriInputDevice::Mouse);
    QVERIFY(var.isValid());

    QCOMPARE(var.value<LomiriInputDevice::InputType>(),
             LomiriInputDevice::Mouse);

    QVector<LomiriInputDevice*> result;

    bool ok = QMetaObject::invokeMethod(
        manager,
        "deviceListOfType",
        Q_RETURN_ARG(QVector<LomiriInputDevice*>, result),
        Q_ARG(LomiriInputDevice::InputType, LomiriInputDevice::Mouse)
        );

    QVERIFY(ok);
}

QTEST_MAIN(TestQInputInfo)
#include "tst_qinputinfo.moc"
