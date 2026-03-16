#include <QtTest>
#include <QDBusObjectPath>
#include "../../applicationmenuregistry.h"

class TestMenuServicePath : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testConstructionAndProperties();
};

void TestMenuServicePath::testConstructionAndProperties()
{
    QString service("com.example.test.app");
    QDBusObjectPath menuPath("/com/example/menu/test");
    QDBusObjectPath actionPath("/com/example/action/test");

    MenuServicePath *path = new MenuServicePath(service, menuPath, actionPath);
    QVERIFY(path != nullptr);
    QVERIFY(qobject_cast<QObject*>(path) != nullptr);
    
    QCOMPARE(path->m_service, QByteArray("com.example.test.app"));
    QCOMPARE(path->m_menuPath, QByteArray("/com/example/menu/test"));
    QCOMPARE(path->m_actionPath, QByteArray("/com/example/action/test"));
    
    delete path;
}

QTEST_MAIN(TestMenuServicePath)
#include "tst_menuservicepath.moc"
