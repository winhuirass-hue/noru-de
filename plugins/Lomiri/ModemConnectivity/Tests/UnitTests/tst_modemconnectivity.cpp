#include <QtTest>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusConnectionInterface>

#include "../../ModemConnectivity.h"

class TestModemConnectivity : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void init();
    void cleanup();

    void testObjectCreation();
    void testDBusConnectionAvailable();
    void testUnlockAllModemsDoesNotCrash();

private:
    ModemConnectivity *m_connectivity;
};

void TestModemConnectivity::initTestCase()
{
    QVERIFY(QDBusConnection::sessionBus().isConnected());
}

void TestModemConnectivity::init()
{
    m_connectivity = new ModemConnectivity();
    QVERIFY(m_connectivity != nullptr);
}

void TestModemConnectivity::cleanup()
{
    delete m_connectivity;
    m_connectivity = nullptr;
}

void TestModemConnectivity::testObjectCreation()
{
    QVERIFY(m_connectivity != nullptr);
}

void TestModemConnectivity::testDBusConnectionAvailable()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    QVERIFY(bus.isConnected());
}

void TestModemConnectivity::testUnlockAllModemsDoesNotCrash()
{
    QVERIFY(m_connectivity != nullptr);

    m_connectivity->unlockAllModems();

    QVERIFY(true);
}

QTEST_MAIN(TestModemConnectivity)
#include "tst_modemconnectivity.moc"
