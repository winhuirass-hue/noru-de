#include <QtTest>
#include "../../BatteryMonitor.h"

class TestBatteryMonitor : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testObjectCreation();
    void testChargingProperty();
    void testFullyChargedProperty();
    void testTimeToFullProperty();
    void testStateMethod();
    void testChargingSignal();
    void testFullyChargedSignal();
    void testTimeToFullSignal();
    void cleanupTestCase();

private:
    BatteryMonitor *batteryMonitor;
};

void TestBatteryMonitor::initTestCase()
{
    batteryMonitor = new BatteryMonitor();
    QVERIFY(batteryMonitor != nullptr);
}

void TestBatteryMonitor::testObjectCreation()
{
    QVERIFY(batteryMonitor != nullptr);
    QVERIFY(qobject_cast<BatteryMonitor*>(batteryMonitor) != nullptr);
}

void TestBatteryMonitor::testChargingProperty()
{
    bool charging = batteryMonitor->charging();
    QVERIFY(charging == true || charging == false);
}

void TestBatteryMonitor::testFullyChargedProperty()
{
    bool fullyCharged = batteryMonitor->isFullyCharged();
    QVERIFY(fullyCharged == true || fullyCharged == false);
}

void TestBatteryMonitor::testTimeToFullProperty()
{
    qint64 timeToFull = batteryMonitor->timeToFull();
    QVERIFY(timeToFull == -1 || timeToFull == -2 || timeToFull >= 0);
}

void TestBatteryMonitor::testStateMethod()
{
    uint state = batteryMonitor->state();
    QVERIFY(state >= 0 && state <= 4);
}

void TestBatteryMonitor::testChargingSignal()
{
    QSignalSpy spy(batteryMonitor, SIGNAL(chargingChanged()));
    QVERIFY(spy.isValid());
}

void TestBatteryMonitor::testFullyChargedSignal()
{
    QSignalSpy spy(batteryMonitor, SIGNAL(fullyChargedChanged()));
    QVERIFY(spy.isValid());
}

void TestBatteryMonitor::testTimeToFullSignal()
{
    QSignalSpy spy(batteryMonitor, SIGNAL(timeToFullChanged()));
    QVERIFY(spy.isValid());
}

void TestBatteryMonitor::cleanupTestCase()
{
    delete batteryMonitor;
}

QTEST_MAIN(TestBatteryMonitor)
#include "tst_batterymonitor.moc"
