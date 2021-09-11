#include <QtTest/QtTest>
#include <valuespec.h>

class TestFunction : public QObject
{
    Q_OBJECT

    using VS = ValueSpec;
private slots:
};

QTEST_MAIN(TestFunction)
#include "function.moc"
