#include <QtTest>
#include <QSignalSpy>
#include "../../qdeclarativeinputdevicemodel_p.h"

class TestQDeclarativeInputDeviceModel : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();

    void testBasics();
    void testRoles();
    void testPropertiesAndSignals();
    void testInvokable();
    void testMetaObject();

private:
    QDeclarativeInputDeviceModel *model;
};


void TestQDeclarativeInputDeviceModel::initTestCase()
{
    model = new QDeclarativeInputDeviceModel();
    QVERIFY(model != nullptr);

    qRegisterMetaType<LomiriInputDevice::InputType>("LomiriInputDevice::InputType");
}

void TestQDeclarativeInputDeviceModel::cleanupTestCase()
{
    delete model;
    model = nullptr;
}

void TestQDeclarativeInputDeviceModel::init()
{
    model->setDeviceFilter(LomiriInputDevice::Unknown);
}

void TestQDeclarativeInputDeviceModel::testBasics()
{
    int count = model->rowCount();
    QVERIFY(count >= 0);

    if (count > 0) {
        QModelIndex index = model->index(0, 0);
        QVERIFY(index.isValid());

        QVERIFY(model->data(index, QDeclarativeInputDeviceModel::NameRole).isValid());
        QVERIFY(model->data(index, QDeclarativeInputDeviceModel::DevicePathRole).isValid());
    }
}

void TestQDeclarativeInputDeviceModel::testRoles()
{
    auto roles = model->roleNames();

    QVERIFY(roles.contains(QDeclarativeInputDeviceModel::NameRole));
    QVERIFY(roles.contains(QDeclarativeInputDeviceModel::DevicePathRole));

    QCOMPARE(roles[QDeclarativeInputDeviceModel::NameRole], QByteArray("name"));
}

void TestQDeclarativeInputDeviceModel::testPropertiesAndSignals()
{
    QSignalSpy filterSpy(model,
                         SIGNAL(deviceFilterChanged(LomiriInputDevice::InputType)));

    QSignalSpy countSpy(model, SIGNAL(countChanged()));

    QVERIFY(filterSpy.isValid());
    QVERIFY(countSpy.isValid());

    model->setDeviceFilter(LomiriInputDevice::Mouse);
    QCOMPARE(model->deviceFilter(), LomiriInputDevice::Mouse);
    QCOMPARE(filterSpy.count(), 1);

    model->setDeviceFilter(LomiriInputDevice::Mouse);
    QCOMPARE(filterSpy.count(), 1);

    QVERIFY(model->property("count").isValid());
}


void TestQDeclarativeInputDeviceModel::testInvokable()
{
    int count = model->rowCount();

    if (count > 0) {
        LomiriInputDevice *dev = model->get(0);
        QVERIFY(dev != nullptr);

        QString path = dev->devicePath();
        QVERIFY(model->indexOf(path) >= 0);
    }

    QCOMPARE(model->indexOf("invalid"), -1);
    QCOMPARE(model->get(-1), nullptr);
    QCOMPARE(model->get(999), nullptr);
}

void TestQDeclarativeInputDeviceModel::testMetaObject()
{
    const QMetaObject *meta = model->metaObject();

    QVERIFY(meta->indexOfProperty("deviceFilter") != -1);
    QVERIFY(meta->indexOfProperty("count") != -1);

    QVERIFY(meta->indexOfMethod("indexOf(QString)") != -1);
    QVERIFY(meta->indexOfMethod("get(int)") != -1);
}

QTEST_MAIN(TestQDeclarativeInputDeviceModel)
#include "tst_qdeclarativeinputdevicemodel.moc"
