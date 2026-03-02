#include <QtTest>
#include <QObject>
#include <QFile>
#include <QDebug>
#include "../../uinput.h"

class TestUInput : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testObjectCreation();
    void testButtonEnumValues();
    void testButtonEnumValidity();
    void testCreateMouseMethod();
    void testRemoveMouseMethod();
    void testRemoveMouseWithoutCreate();
    void testMoveMouseMethod();
    void testMoveMouseWithoutCreate();
    void testPressMouseMethod();
    void testPressMouseWithoutCreate();
    void testReleaseMouseMethod();
    void testReleaseMouseWithoutCreate();
    void testScrollMouseMethod();
    void testScrollMouseWithoutCreate();
    void testDoubleCreate();
    void testCompleteMouseSequence();
    void testMouseSequenceWithAllButtons();
    void testVariousMovementValues();
    void testVariousScrollValues();
    void testStateAfterCreation();
    void testStateAfterRemoval();
    void cleanupTestCase();

private:
    UInput *uinput;
    bool hasUInputAccess();
};

bool TestUInput::hasUInputAccess()
{
    QFile uinputFile("/dev/uinput");
    return uinputFile.exists();
}


void TestUInput::initTestCase()
{
    uinput = new UInput();
    QVERIFY(uinput != nullptr);
    
    if (!hasUInputAccess()) {
        qWarning() << "======================================================";
        qWarning() << "/dev/uinput not accessible. This test requires root.";
        qWarning() << "Run with: sudo ./UInputTest";
        qWarning() << "======================================================";
    }
}

void TestUInput::testObjectCreation()
{
    QVERIFY(uinput != nullptr);
    QVERIFY(qobject_cast<UInput*>(uinput) != nullptr);
    QCOMPARE(QString::fromUtf8(uinput->metaObject()->className()), "UInput");
}

void TestUInput::testButtonEnumValues()
{
    QCOMPARE(static_cast<int>(UInput::ButtonLeft), 0);
    QCOMPARE(static_cast<int>(UInput::ButtonRight), 1);
    QCOMPARE(static_cast<int>(UInput::ButtonMiddle), 2);
}

void TestUInput::testButtonEnumValidity()
{
    UInput::Button left = UInput::ButtonLeft;
    UInput::Button right = UInput::ButtonRight;
    UInput::Button middle = UInput::ButtonMiddle;

    QVERIFY(left == UInput::ButtonLeft);
    QVERIFY(right == UInput::ButtonRight);
    QVERIFY(middle == UInput::ButtonMiddle);
    QVERIFY(left != right);
    QVERIFY(right != middle);
    QVERIFY(left != middle);
}

void TestUInput::testCreateMouseMethod()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->createMouse();
    } catch (const std::exception &e) {
        QFAIL(QString("createMouse() threw exception: %1").arg(e.what()).toLatin1());
    } catch (...) {
        QFAIL("createMouse() threw an unknown exception");
    }

    uinput->removeMouse();
}


void TestUInput::testRemoveMouseMethod()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->removeMouse();
    } catch (const std::exception &e) {
        QFAIL(QString("removeMouse() threw exception: %1").arg(e.what()).toLatin1());
    } catch (...) {
        QFAIL("removeMouse() threw an unknown exception");
    }
}

void TestUInput::testRemoveMouseWithoutCreate()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->removeMouse();
    } catch (...) {
    }

    try {
        uinput->removeMouse();
    } catch (...) {
        QFAIL("removeMouse() without create should not throw");
    }
}

void TestUInput::testMoveMouseMethod()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->moveMouse(10, 0);
        uinput->moveMouse(-10, 0);
        uinput->moveMouse(0, 10);
        uinput->moveMouse(0, -10);
    } catch (...) {
        QFAIL("moveMouse() threw an exception");
    }

    uinput->removeMouse();
}

void TestUInput::testMoveMouseWithoutCreate()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->removeMouse();
    } catch (...) {
    }

    try {
        uinput->moveMouse(10, 10);
    } catch (...) {
        QFAIL("moveMouse() without create should not throw");
    }
}

void TestUInput::testVariousMovementValues()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->moveMouse(5, 5);
        uinput->moveMouse(100, 100);
        uinput->moveMouse(1000, 1000);

        uinput->moveMouse(-5, -5);
        uinput->moveMouse(-100, -100);
        uinput->moveMouse(-1000, -1000);

        uinput->moveMouse(50, -50);
        uinput->moveMouse(-50, 50);

        uinput->moveMouse(0, 0);

    } catch (...) {
        QFAIL("moveMouse() with various values threw exception");
    }

    uinput->removeMouse();
}

void TestUInput::testPressMouseMethod()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->pressMouse(UInput::ButtonLeft);
        uinput->pressMouse(UInput::ButtonRight);
        uinput->pressMouse(UInput::ButtonMiddle);
    } catch (...) {
        QFAIL("pressMouse() threw an exception");
    }

    uinput->removeMouse();
}

void TestUInput::testPressMouseWithoutCreate()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->removeMouse();
    } catch (...) {
    }

    try {
        uinput->pressMouse(UInput::ButtonLeft);
    } catch (...) {
        QFAIL("pressMouse() without create should not throw");
    }
}

void TestUInput::testReleaseMouseMethod()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->releaseMouse(UInput::ButtonLeft);
        uinput->releaseMouse(UInput::ButtonRight);
        uinput->releaseMouse(UInput::ButtonMiddle);
    } catch (...) {
        QFAIL("releaseMouse() threw an exception");
    }

    uinput->removeMouse();
}

void TestUInput::testReleaseMouseWithoutCreate()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->removeMouse();
    } catch (...) {
    }

    try {
        uinput->releaseMouse(UInput::ButtonLeft);
    } catch (...) {
        QFAIL("releaseMouse() without create should not throw");
    }
}

void TestUInput::testScrollMouseMethod()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->scrollMouse(0, 5);
        uinput->scrollMouse(0, -5);
        uinput->scrollMouse(5, 0);
        uinput->scrollMouse(-5, 0);
    } catch (...) {
        QFAIL("scrollMouse() threw an exception");
    }

    uinput->removeMouse();
}

void TestUInput::testScrollMouseWithoutCreate()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->removeMouse();
    } catch (...) {
    }

    try {
        uinput->scrollMouse(5, 5);
    } catch (...) {
        QFAIL("scrollMouse() without create should not throw");
    }
}

void TestUInput::testVariousScrollValues()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->scrollMouse(0, 1);
        uinput->scrollMouse(0, 5);
        uinput->scrollMouse(0, 10);
        uinput->scrollMouse(0, -1);
        uinput->scrollMouse(0, -5);
        uinput->scrollMouse(0, -10);

        uinput->scrollMouse(1, 0);
        uinput->scrollMouse(5, 0);
        uinput->scrollMouse(10, 0);
        uinput->scrollMouse(-1, 0);
        uinput->scrollMouse(-5, 0);
        uinput->scrollMouse(-10, 0);

        uinput->scrollMouse(3, 3);
        uinput->scrollMouse(5, -5);
        uinput->scrollMouse(-3, 3);
        uinput->scrollMouse(-5, -5);

        uinput->scrollMouse(0, 0);

    } catch (...) {
        QFAIL("scrollMouse() with various values threw exception");
    }

    uinput->removeMouse();
}

void TestUInput::testStateAfterCreation()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();

    try {
        uinput->moveMouse(10, 10);
        uinput->pressMouse(UInput::ButtonLeft);
        uinput->releaseMouse(UInput::ButtonLeft);
        uinput->scrollMouse(0, 5);
    } catch (...) {
        QFAIL("Operations failed after creation");
    }

    uinput->removeMouse();
}

void TestUInput::testStateAfterRemoval()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    uinput->createMouse();
    uinput->removeMouse();

    try {
        uinput->moveMouse(10, 10);
        uinput->pressMouse(UInput::ButtonLeft);
        uinput->scrollMouse(0, 5);
    } catch (...) {
        QFAIL("Operations should be safe after removal");
    }
}

void TestUInput::testDoubleCreate()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->createMouse();
        uinput->createMouse();
    } catch (...) {
        QFAIL("Double create should be handled gracefully");
    }

    uinput->removeMouse();
}

void TestUInput::testCompleteMouseSequence()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->createMouse();

        uinput->moveMouse(100, 100);

        uinput->pressMouse(UInput::ButtonLeft);
        uinput->releaseMouse(UInput::ButtonLeft);

        uinput->moveMouse(-50, 50);

        uinput->pressMouse(UInput::ButtonRight);
        uinput->releaseMouse(UInput::ButtonRight);

        uinput->scrollMouse(0, -3);

        uinput->removeMouse();

    } catch (...) {
        QFAIL("Complete mouse sequence failed");
    }
}

void TestUInput::testMouseSequenceWithAllButtons()
{
    if (!hasUInputAccess()) {
        QSKIP("/dev/uinput not accessible - skipping hardware test");
    }

    try {
        uinput->createMouse();

        for (int i = 0; i < 2; ++i) {
            uinput->pressMouse(UInput::ButtonLeft);
            uinput->releaseMouse(UInput::ButtonLeft);

            uinput->pressMouse(UInput::ButtonRight);
            uinput->releaseMouse(UInput::ButtonRight);

            uinput->pressMouse(UInput::ButtonMiddle);
            uinput->releaseMouse(UInput::ButtonMiddle);
        }

        uinput->removeMouse();
    } catch (...) {
        QFAIL("All button sequence failed");
    }
}

void TestUInput::cleanupTestCase()
{
    if (!uinput) {
        return;
    }

    try {
        uinput->removeMouse();
    } catch (...) {
    }

    delete uinput;
    uinput = nullptr;
}

QTEST_MAIN(TestUInput)
#include "tst_uinput.moc"
