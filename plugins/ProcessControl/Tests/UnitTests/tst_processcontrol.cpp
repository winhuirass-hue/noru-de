#include <QtTest>
#include <QSignalSpy>
#include "../../ProcessControl.h"

class TestProcessControl: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testDefaultValue();
    void testSetAwakenProcesses();
    void testSignalEmission();
    void cleanupTestCase();

private:
    ProcessControl* m_processControl;
};

void TestProcessControl::initTestCase()
{
    m_processControl = new ProcessControl;
}

void TestProcessControl::testDefaultValue()
{
    QStringList list = m_processControl->awakenProcesses();
    QVERIFY(list.isEmpty());
}

void TestProcessControl::testSetAwakenProcesses()
{
    QStringList processes;
    processes << "app1";

    m_processControl->setAwakenProcesses(processes);
    QCOMPARE(m_processControl->awakenProcesses(), processes);
}

void TestProcessControl::testSignalEmission()
{

    QSignalSpy spy(m_processControl, &ProcessControl::awakenProcessesChanged);

    QStringList processes;
    processes << "app2";

    m_processControl->setAwakenProcesses(processes);

    QCOMPARE(spy.count(), 1);
}

void TestProcessControl::cleanupTestCase()
{
    delete m_processControl;
}

QTEST_MAIN(TestProcessControl)
#include "tst_processcontrol.moc"
