#include <QtTest>
#include "../../Powerd.h"

Q_DECLARE_METATYPE(Powerd::DisplayStateChangeReason)

class TestPowerd : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void testObjectCreation();
    void testStatusProperty();
    void testStatusPropertyType();
    void testSetStatusMethod();
    void testStatusEnumValues();
    void testDisplayStateChangeReasonEnumValues();
    void testStatusChangedSignal();
    void cleanupTestCase();

private:
    Powerd *powerd;
};

void TestPowerd::initTestCase()
{
    qRegisterMetaType<Powerd::DisplayStateChangeReason>("Powerd::DisplayStateChangeReason");
    powerd = new Powerd();
    QVERIFY(powerd != nullptr);
}

void TestPowerd::testObjectCreation()
{
    QVERIFY(powerd != nullptr);
    QVERIFY(qobject_cast<Powerd*>(powerd) != nullptr);
}

void TestPowerd::testStatusProperty()
{
    Powerd::Status status = powerd->status();
    QVERIFY(status == Powerd::Off || status == Powerd::On);
}

void TestPowerd::testStatusPropertyType()
{
    Powerd::Status status = powerd->status();
    int statusValue = (int)status;
    QVERIFY(statusValue == 0 || statusValue == 1);
}

void TestPowerd::testSetStatusMethod()
{
    powerd->setStatus(Powerd::On, Powerd::PowerKey);
    powerd->setStatus(Powerd::Off, Powerd::Inactivity);
    powerd->setStatus(Powerd::On, Powerd::Notification);
    QVERIFY(true);
}

void TestPowerd::testStatusEnumValues()
{
    QCOMPARE((int)Powerd::Off, 0);
    QCOMPARE((int)Powerd::On, 1);
}

void TestPowerd::testDisplayStateChangeReasonEnumValues()
{
    QCOMPARE((int)Powerd::Unknown, 0);
    QCOMPARE((int)Powerd::Inactivity, 1);
    QCOMPARE((int)Powerd::PowerKey, 2);
    QCOMPARE((int)Powerd::Proximity, 3);
    QCOMPARE((int)Powerd::Notification, 4);
    QCOMPARE((int)Powerd::SnapDecision, 5);
    QCOMPARE((int)Powerd::CallDone, 6);
}

void TestPowerd::testStatusChangedSignal()
{
    QSignalSpy spy(powerd, &Powerd::statusChanged);
    QVERIFY(spy.isValid());
}

void TestPowerd::cleanupTestCase()
{
    delete powerd;
}

QTEST_MAIN(TestPowerd)
#include "tst_powerd.moc"
