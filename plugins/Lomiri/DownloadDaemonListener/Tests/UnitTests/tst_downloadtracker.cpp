#include <QtTest>
#include <QSignalSpy>
#include "DownloadTracker.h"

class TestDownloadTracker : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void testPropertiesInitiallyEmpty();
    void testSetAndGetServiceProperty();
    void testSetAndGetDbusPathProperty();
    void testServiceChangedSignalEmitted();
    void testDbusPathChangedSignalEmitted();
    void testServiceReadySignal();
    void testServiceNoDuplicateSignal();
    void testPathNoDuplicateSignal();
    void testIndependentProperties();

private:
    DownloadTracker *downloadTracker;
};

void TestDownloadTracker::init()
{
    downloadTracker = new DownloadTracker();
    QVERIFY(downloadTracker != nullptr);
}

void TestDownloadTracker::cleanup()
{
    delete downloadTracker;
    downloadTracker = nullptr;
}

void TestDownloadTracker::testPropertiesInitiallyEmpty()
{
    QCOMPARE(downloadTracker->service(), QString());
    QCOMPARE(downloadTracker->dbusPath(), QString());
    QCOMPARE(downloadTracker->isServiceReady(), false);
}

void TestDownloadTracker::testSetAndGetServiceProperty()
{
    const QString testService = "com.ubuntu.downloads";
    downloadTracker->setService(testService);
    QCOMPARE(downloadTracker->service(), testService);
}

void TestDownloadTracker::testSetAndGetDbusPathProperty()
{
    const QString testPath = "/com/ubuntu/downloads/1";
    downloadTracker->setDbusPath(testPath);
    QCOMPARE(downloadTracker->dbusPath(), testPath);
}

void TestDownloadTracker::testServiceChangedSignalEmitted()
{
    QSignalSpy spy(downloadTracker, SIGNAL(serviceChanged(const QString &)));

    const QString testService = "com.ubuntu.downloads";
    downloadTracker->setService(testService);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), testService);
}

void TestDownloadTracker::testDbusPathChangedSignalEmitted()
{
    QSignalSpy spy(downloadTracker, SIGNAL(dbusPathChanged(const QString &)));

    const QString testPath = "/com/ubuntu/downloads/1";
    downloadTracker->setDbusPath(testPath);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), testPath);
}

void TestDownloadTracker::testServiceReadySignal()
{
    QSignalSpy spy(downloadTracker, SIGNAL(serviceReadyChanged(bool)));

    QVERIFY(spy.isValid());
    downloadTracker->setService("com.ubuntu.downloads");
    QCOMPARE(spy.count(), 1);
}

void TestDownloadTracker::testServiceNoDuplicateSignal()
{
    QSignalSpy spy(downloadTracker, SIGNAL(serviceChanged(const QString &)));

    const QString testService = "com.ubuntu.downloads";
    downloadTracker->setService(testService);
    QCOMPARE(spy.count(), 1);

    downloadTracker->setService(testService);
    QCOMPARE(spy.count(), 1);
}

void TestDownloadTracker::testPathNoDuplicateSignal()
{
    QSignalSpy spy(downloadTracker, SIGNAL(dbusPathChanged(const QString &)));

    const QString testPath = "/com/ubuntu/downloads/1";
    downloadTracker->setDbusPath(testPath);
    QCOMPARE(spy.count(), 1);

    downloadTracker->setDbusPath(testPath);
    QCOMPARE(spy.count(), 1);
}

void TestDownloadTracker::testIndependentProperties()
{
    const QString testService = "com.ubuntu.downloads";
    const QString testPath = "/com/ubuntu/downloads/1";

    downloadTracker->setDbusPath(testPath);
    QCOMPARE(downloadTracker->dbusPath(), testPath);
    QCOMPARE(downloadTracker->service(), QString());

    downloadTracker->setService(testService);
    QCOMPARE(downloadTracker->service(), testService);
    QCOMPARE(downloadTracker->dbusPath(), testPath);
}

QTEST_MAIN(TestDownloadTracker)
#include "tst_downloadtracker.moc"
