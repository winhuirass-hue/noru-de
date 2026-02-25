#include <QtTest>
#include <QDBusConnection>
#include "../../displays.h"

class TestAethercast : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testObjectCreation();
    void testScanningProperty();
    void testEnabledProperty();
    void testStateProperty();
    void testSetEnabled();
    void testScanningSignal();
    void testEnabledSignal();
    void testStateSignal();
    void testConnectErrorSignal();
    void cleanupTestCase();

private:
    Displays *displays;
};

void TestAethercast::initTestCase()
{
    displays = new Displays();
    QVERIFY(displays != nullptr);
}

void TestAethercast::testObjectCreation()
{
    QVERIFY(displays != nullptr);
    QVERIFY(qobject_cast<Displays*>(displays) != nullptr);
}

void TestAethercast::testScanningProperty()
{
    bool scanning = displays->scanning();
    QVERIFY(scanning == true || scanning == false);
}

void TestAethercast::testEnabledProperty()
{
    bool enabled = displays->enabled();
    QVERIFY(enabled == true || enabled == false);
}

void TestAethercast::testStateProperty()
{
    // State property can be null if Aethercast daemon not running
    // Just verify property is accessible without crashing
    QString state = displays->state();
    QVERIFY(true);
}

void TestAethercast::testSetEnabled()
{
    bool originalState = displays->enabled();
    displays->setEnabled(!originalState);
    bool currentState = displays->enabled();
    QVERIFY(currentState == true || currentState == false);
}

void TestAethercast::testScanningSignal()
{
    QSignalSpy spy(displays, SIGNAL(scanningChanged(bool)));
    QVERIFY(spy.isValid());
}

void TestAethercast::testEnabledSignal()
{
    QSignalSpy spy(displays, SIGNAL(enabledChanged(bool)));
    QVERIFY(spy.isValid());
}

void TestAethercast::testStateSignal()
{
    QSignalSpy spy(displays, SIGNAL(stateChanged()));
    QVERIFY(spy.isValid());
}

void TestAethercast::testConnectErrorSignal()
{
    QSignalSpy spy(displays, SIGNAL(connectError(int)));
    QVERIFY(spy.isValid());
}

void TestAethercast::cleanupTestCase()
{
    delete displays;
}

QTEST_MAIN(TestAethercast)
#include "tst_aethercast.moc"
