#include <QtTest>
#include <QSignalSpy>
#include <QDBusObjectPath>
#include "../../applicationmenuregistry.h"
#include "../../dbusapplicationmenuregistry.h"

class TestApplicationMenuRegistry : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void testSingletonInstance();
    void testAppMenuRegistrationAndUnregistration();
    void testSurfaceMenuRegistrationAndUnregistration();
    void testGetMenusForSurface();
    void testDuplicateMenuPrevention();
    void testMultipleMenusPerSurface();
    void testMultipleMenusPerApp();

private:
    ApplicationMenuRegistry *m_registry;
};

void TestApplicationMenuRegistry::initTestCase()
{
    m_registry = DBusApplicationMenuRegistry::instance();
    QVERIFY(m_registry != nullptr);
}

void TestApplicationMenuRegistry::testSingletonInstance()
{
    ApplicationMenuRegistry *instance1 = DBusApplicationMenuRegistry::instance();
    ApplicationMenuRegistry *instance2 = DBusApplicationMenuRegistry::instance();

    QVERIFY(instance1 != nullptr);
    QVERIFY(instance2 != nullptr);
    QCOMPARE(instance1, instance2);
    
    DBusApplicationMenuRegistry *dbusInstance = qobject_cast<DBusApplicationMenuRegistry*>(instance1);
    QVERIFY(dbusInstance != nullptr);
}

void TestApplicationMenuRegistry::testAppMenuRegistrationAndUnregistration()
{
    pid_t pid = 6000;
    QDBusObjectPath menuPath("/com/test/app/menu1");
    QDBusObjectPath actionPath("/com/test/app/action1");

    QSignalSpy registerSpy(m_registry, SIGNAL(appMenuRegistered(uint)));
    QVERIFY(registerSpy.isValid());
    
    m_registry->RegisterAppMenu(pid, menuPath, actionPath, "com.example.test.app1");
    QCOMPARE(registerSpy.count(), 1);
    QCOMPARE(registerSpy.at(0).at(0).toUInt(), static_cast<uint>(pid));

    QSignalSpy unregisterSpy(m_registry, SIGNAL(appMenuUnregistered(uint)));
    m_registry->UnregisterAppMenu(pid, menuPath);
    
    QCOMPARE(unregisterSpy.count(), 1);
    QCOMPARE(unregisterSpy.at(0).at(0).toUInt(), static_cast<uint>(pid));
}

void TestApplicationMenuRegistry::testSurfaceMenuRegistrationAndUnregistration()
{
    QString surfaceId("surface-test1");
    QDBusObjectPath menuPath("/com/test/surface/menu1");
    QDBusObjectPath actionPath("/com/test/surface/action1");

    QSignalSpy registerSpy(m_registry, SIGNAL(surfaceMenuRegistered(QString)));
    QVERIFY(registerSpy.isValid());

    m_registry->RegisterSurfaceMenu(surfaceId, menuPath, actionPath, "com.example.test.surface1");
    QCOMPARE(registerSpy.count(), 1);
    QCOMPARE(registerSpy.at(0).at(0).toString(), surfaceId);

    QSignalSpy unregisterSpy(m_registry, SIGNAL(surfaceMenuUnregistered(QString)));
    m_registry->UnregisterSurfaceMenu(surfaceId, menuPath);

    QCOMPARE(unregisterSpy.count(), 1);
    QCOMPARE(unregisterSpy.at(0).at(0).toString(), surfaceId);
}

void TestApplicationMenuRegistry::testGetMenusForSurface()
{
    QString surfaceId("surface-test3");
    QDBusObjectPath menuPath("/com/test/surface/menu3");
    QDBusObjectPath actionPath("/com/test/surface/action3");

    m_registry->RegisterSurfaceMenu(surfaceId, menuPath, actionPath, "com.example.test.surface3");

    QList<QObject*> menus = m_registry->getMenusForSurface(surfaceId);
    QVERIFY(!menus.isEmpty());
    QVERIFY(menus.at(0) != nullptr);

    auto menuServicePath = qobject_cast<MenuServicePath*>(menus.at(0));
    QVERIFY(menuServicePath != nullptr);
    QCOMPARE(menuServicePath->m_service, QByteArray("com.example.test.surface3"));

    QString nonExistentSurface("surface-nonexistent-xyz123");
    QList<QObject*> emptyMenus = m_registry->getMenusForSurface(nonExistentSurface);
    QCOMPARE(emptyMenus.count(), 0);
}

void TestApplicationMenuRegistry::testDuplicateMenuPrevention()
{
    QSignalSpy appSpy(m_registry, SIGNAL(appMenuRegistered(uint)));
    int appInitialCount = appSpy.count();

    pid_t pid = 6002;
    QDBusObjectPath menuPath("/com/test/app/menu_dup");
    QDBusObjectPath actionPath("/com/test/app/action_dup");

    m_registry->RegisterAppMenu(pid, menuPath, actionPath, "com.example.test.appdup");
    QCOMPARE(appSpy.count(), appInitialCount + 1);

    int appCountAfterFirst = appSpy.count();
    m_registry->RegisterAppMenu(pid, menuPath, actionPath, "com.example.test.appdup");
    QCOMPARE(appSpy.count(), appCountAfterFirst);

    QSignalSpy surfaceSpy(m_registry, SIGNAL(surfaceMenuRegistered(QString)));
    int surfaceInitialCount = surfaceSpy.count();

    QString surfaceId("surface-test-dup");
    QDBusObjectPath surfaceMenuPath("/com/test/surface/menu_dup");
    QDBusObjectPath surfaceActionPath("/com/test/surface/action_dup");

    m_registry->RegisterSurfaceMenu(surfaceId, surfaceMenuPath, surfaceActionPath, "com.example.test.surfacedup");
    QCOMPARE(surfaceSpy.count(), surfaceInitialCount + 1);

    int surfaceCountAfterFirst = surfaceSpy.count();
    m_registry->RegisterSurfaceMenu(surfaceId, surfaceMenuPath, surfaceActionPath, "com.example.test.surfacedup");
    QCOMPARE(surfaceSpy.count(), surfaceCountAfterFirst);
}

void TestApplicationMenuRegistry::testMultipleMenusPerSurface()
{
    QString surfaceId("surface-multi-test");

    QDBusObjectPath menuPath1("/com/test/surface/multi1");
    QDBusObjectPath actionPath1("/com/test/surface/action_multi1");
    m_registry->RegisterSurfaceMenu(surfaceId, menuPath1, actionPath1, "com.example.test.multiapp1");

    QDBusObjectPath menuPath2("/com/test/surface/multi2");
    QDBusObjectPath actionPath2("/com/test/surface/action_multi2");
    m_registry->RegisterSurfaceMenu(surfaceId, menuPath2, actionPath2, "com.example.test.multiapp2");

    QList<QObject*> menus = m_registry->getMenusForSurface(surfaceId);
    QCOMPARE(menus.count(), 2);

    QByteArray service1 = qobject_cast<MenuServicePath*>(menus.at(0))->m_service;
    QByteArray service2 = qobject_cast<MenuServicePath*>(menus.at(1))->m_service;

    QVERIFY((service1 == QByteArray("com.example.test.multiapp1") || 
             service1 == QByteArray("com.example.test.multiapp2")));
    QVERIFY((service2 == QByteArray("com.example.test.multiapp1") || 
             service2 == QByteArray("com.example.test.multiapp2")));
    QVERIFY(service1 != service2);
}

void TestApplicationMenuRegistry::testMultipleMenusPerApp()
{
    pid_t pid = 6003;

    QDBusObjectPath menuPath1("/com/test/app/app_multi1");
    QDBusObjectPath actionPath1("/com/test/app/action_app_multi1");
    m_registry->RegisterAppMenu(pid, menuPath1, actionPath1, "com.example.test.appmulti");

    QDBusObjectPath menuPath2("/com/test/app/app_multi2");
    QDBusObjectPath actionPath2("/com/test/app/action_app_multi2");
    m_registry->RegisterAppMenu(pid, menuPath2, actionPath2, "com.example.test.appmulti");

    QVERIFY(true);
}

QTEST_MAIN(TestApplicationMenuRegistry)
#include "tst_applicationmenuregistry.moc"
