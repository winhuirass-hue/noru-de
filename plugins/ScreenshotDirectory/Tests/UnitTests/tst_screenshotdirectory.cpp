#include <QtTest>
#include <QTemporaryDir>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QRegularExpression>
#include "../../ScreenshotDirectory.h"

class TestScreenshotDirectory : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testObjectCreation();
    void testMakeFileNameFormat();
    void testMakeFileNameContainsPrefix();
    void testMakeFileNameContainsTimestamp();
    void testMakeFileNameContainsPngExtension();
    void testMultipleFileNamesAreUnique();
    void testMakeFileNameWithValidPath();
    void testFileNameCanBeCreated();
    void cleanupTestCase();

private:
    ScreenshotDirectory *screenshotDirectory;
};

void TestScreenshotDirectory::initTestCase()
{
    qputenv("LOMIRI_TESTING", "1");
    screenshotDirectory = new ScreenshotDirectory();
    QVERIFY(screenshotDirectory != nullptr);
}

void TestScreenshotDirectory::testObjectCreation()
{
    QVERIFY(screenshotDirectory != nullptr);
    QVERIFY(qobject_cast<ScreenshotDirectory*>(screenshotDirectory) != nullptr);
}

void TestScreenshotDirectory::testMakeFileNameFormat()
{
    QString fileName = screenshotDirectory->makeFileName();
    QVERIFY2(!fileName.isEmpty(), "makeFileName should return non-empty string");
    QVERIFY2(fileName.contains(QDir::separator()) || fileName.contains('/'),
             qPrintable(QString("Filename '%1' should contain path separators").arg(fileName)));
}

void TestScreenshotDirectory::testMakeFileNameContainsPrefix()
{
    QString fileName = screenshotDirectory->makeFileName();
    QVERIFY2(fileName.contains("screenshot"),
             qPrintable(QString("Filename '%1' should contain 'screenshot' prefix").arg(fileName)));
}

void TestScreenshotDirectory::testMakeFileNameContainsTimestamp()
{
    QString fileName = screenshotDirectory->makeFileName();

    QRegularExpression dateTimePattern(QStringLiteral("\\d{8}_\\d{9}"));
    QVERIFY2(dateTimePattern.match(fileName).hasMatch(),
             qPrintable(QString("Filename '%1' does not match timestamp pattern yyyyMMdd_hhmmsszzz").arg(fileName)));
}

void TestScreenshotDirectory::testMakeFileNameContainsPngExtension()
{
    QString fileName = screenshotDirectory->makeFileName();
    QVERIFY2(fileName.endsWith(".png"),
             qPrintable(QString("Filename '%1' should end with .png extension").arg(fileName)));
}

void TestScreenshotDirectory::testMultipleFileNamesAreUnique()
{
    QString fileName1 = screenshotDirectory->makeFileName();
    QTest::qWait(10);
    QString fileName2 = screenshotDirectory->makeFileName();
    QTest::qWait(10);
    QString fileName3 = screenshotDirectory->makeFileName();

    QVERIFY(!fileName1.isEmpty());
    QVERIFY(!fileName2.isEmpty());
    QVERIFY(!fileName3.isEmpty());

    QVERIFY2(fileName1 != fileName2,
             qPrintable(QString("First and second filenames should be different:\n%1\n%2").arg(fileName1, fileName2)));
    QVERIFY2(fileName2 != fileName3,
             qPrintable(QString("Second and third filenames should be different:\n%1\n%2").arg(fileName2, fileName3)));
}

void TestScreenshotDirectory::testMakeFileNameWithValidPath()
{
    QString fileName = screenshotDirectory->makeFileName();

    QFileInfo fileInfo(fileName);
    QString dirPath = fileInfo.absolutePath();

    QDir dir(dirPath);
    QVERIFY2(dir.exists(),
             qPrintable(QString("Directory '%1' should exist for filename '%2'").arg(dirPath, fileName)));
}

void TestScreenshotDirectory::testFileNameCanBeCreated()
{
    QString fileName = screenshotDirectory->makeFileName();

    QFileInfo fileInfo(fileName);
    QDir parentDir(fileInfo.absolutePath());

    QVERIFY2(parentDir.exists(),
             qPrintable(QString("Parent directory '%1' should exist").arg(parentDir.absolutePath())));

    QFile testFile(fileName);
    QVERIFY2(testFile.open(QIODevice::WriteOnly),
             qPrintable(QString("Should be able to create file at '%1'").arg(fileName)));
    testFile.close();

    testFile.remove();
}

void TestScreenshotDirectory::cleanupTestCase()
{
    delete screenshotDirectory;
}

QTEST_MAIN(TestScreenshotDirectory)
#include "tst_screenshotdirectory.moc"
